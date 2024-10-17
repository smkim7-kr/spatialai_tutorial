#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <thread>
#define LOG(x) std::cout << x << std::endl

class Timer {
private:
	const char* m_name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	bool m_stopped;
public:
	Timer(const char* name)
		: m_name(name), m_stopped(false)
	{
		m_start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		if(!m_stopped)
			Stop();
	}
	void Stop() {
		auto endtime = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endtime).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << duration << "us, " << ms << "ms\n";
		m_stopped = true;
	}
};

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID; // track threadid used for benchmarking
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
public:
    Instrumentor()
        : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{ name };
    }

    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    void WriteProfile(const ProfileResult& result) // output json file 
    {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush(); // flush because prevent losing profiling data when meeting crash 
    }

    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    static Instrumentor& Get()
    {
        static Instrumentor instance;
        return instance;
    }
};

class InstrumentationTimer
{
public:
	InstrumentationTimer(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        // Instrumentor::Get().WriteProfile({ m_Name, start, end });
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

		m_Stopped = true;
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	bool m_Stopped;
};

// Use macros to define Instructiontimer and name with function name
#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
// #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__) // cannot distinguish overloaded function
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__) // can distinguish with differnt inputs
#else
#define PROFILE_SCOPE(name)
#endif

void Function1() {
	Timer timer("Funciton1");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World! #" << i << std::endl;
}

void Function2() {
	Timer timer("Funciton2");
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World! #" << sqrt(i) << std::endl;
}

namespace Benchmark {
    void Function1v() {
        PROFILE_FUNCTION();
        // InstrumentationTimer timer("Funciton1");
        for (int i = 0; i < 1000; i++)
            std::cout << "Hello World! #" << i << std::endl;
    }

    void Function1v(int a) {
        PROFILE_FUNCTION();
        // InstrumentationTimer timer("Funciton1");
        for (int i = 0; i < 1000; i++)
            std::cout << "Hello World! #" << a+i << std::endl;
    }

    void Function2v() {
        // InstrumentationTimer timer("Funciton2");
        PROFILE_FUNCTION();
        for (int i = 0; i < 1000; i++)
            std::cout << "Hello World! #" << sqrt(i) << std::endl;
    }

    void RunBenchmarks() {
        // InstrumentationTimer timer("RunBenchmarks");
        PROFILE_FUNCTION();

        std::cout << "Running Benchmarks...\n" << std::endl;
        /* Without multithreading
        Function1v();
        Function1v(10);
        Function2v();
        */
        std::thread a([]() {Function1v(); });
        std::thread b([]() {Function1v(10); });
        std::thread c([]() {Function2v(); });

        a.join();
        b.join();
        c.join();
    }
}


int main() {
	// benchmarking without visualization
	Function1();
	Function2();

	// benchmarking visualization: chrome:tracing
	// record json file of timer file
    Instrumentor::Get().BeginSession("Profile");
    Benchmark::Function1v();
    Benchmark::Function2v();
    Instrumentor::Get().EndSession(); // output at results.json file
    // load json file to chrome:tracking

    Instrumentor::Get().BeginSession("Profile2");
    Benchmark::RunBenchmarks();
    Instrumentor::Get().EndSession();
	std::cin.get();
}