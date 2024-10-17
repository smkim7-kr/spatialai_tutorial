// run in parallel, challenge - find out dependencies 
// make worker threads run independently
#include <iostream>
#include <string>
#include <vector>
#include <mutex> // mutex lock-unlock
#include <future> // header file for std::async
#define LOG(x) std::cout << x << std::endl

class Player {
private:
	int backnum;
public:
	Player(int num) { backnum = num; }
	void UpdateNum(int num) { backnum = num; }
};

static std::mutex s_PlayersMutex; // mutex initialization

static void loadSoccerPlayers(std::vector<Player>& soccerplayers, Player& player) {
	std::lock_guard<std::mutex> lock(s_PlayersMutex); // mutex lock
	soccerplayers.push_back(player);
}

int main() {
	std::vector<Player> players;
	std::vector<Player> Soccerplayers;
	std::vector<std::future<void>> threads;

	for (int i = 0; i < 100; ++i)
		players.push_back(Player(i));

#define ASYNC 1
#if ASYNC
	for (const auto& player : players) { 
		threads.push_back(std::async(std::launch::async, loadSoccerPlayers, std::ref(Soccerplayers), std::ref(player))); // work asynchronously on different threads
	}
#else
	for (const auto& player : players)
		Soccerplayers.push_back(player);
#endif

	// Debug >> Windows >> Parallel Stacks
	// can visualize stack traces of different threads running
	std::cin.get();
}