// not required to be used, vital for large projects / not necessary on small/toy projects
// very helpful: grad bunch of header files and convert to compiler format
// e,g. several header files are used everytime #include <vector>, <iostream>, ..
// preprocessor copy the whole files (which is very long) every time we compiler-build to file
// e.g. #include <vector> every translation unit with this header copies the whole file everytime recompiled
// compiler times are lot longer than could be shorten -> precompiled header (bunch of header files compiled only once, converted into binray format)
// do not add frequently changing files into precompiled header 
// code never going to be touched (e.g. STL, WIndows API) must be in precompuled header files 
// PCH can hide what is actually being used (cpp file itself doesn't tell which dependencies are used - difficult to code readers)
// maybe don't /include all dependencies for the clarity of the reader (e.g. if only single cpp file uses header, just includ in cpp file)
// std::cout, string, vector are boardly used library, add to precompiled headers!

// #include "StdAfx.h" // default precompiled header in Visual Studio
#include "pch.h" // generate *.gch file

int main() {

	std::cin.get();
}