# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build

# Include any dependencies generated for this target.
include CMakeFiles/AnotherProgram.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AnotherProgram.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AnotherProgram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AnotherProgram.dir/flags.make

CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o: CMakeFiles/AnotherProgram.dir/flags.make
CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o: ../src/another_main.cpp
CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o: CMakeFiles/AnotherProgram.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o -MF CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o.d -o CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o -c /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/src/another_main.cpp

CMakeFiles/AnotherProgram.dir/src/another_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnotherProgram.dir/src/another_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/src/another_main.cpp > CMakeFiles/AnotherProgram.dir/src/another_main.cpp.i

CMakeFiles/AnotherProgram.dir/src/another_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnotherProgram.dir/src/another_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/src/another_main.cpp -o CMakeFiles/AnotherProgram.dir/src/another_main.cpp.s

# Object files for target AnotherProgram
AnotherProgram_OBJECTS = \
"CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o"

# External object files for target AnotherProgram
AnotherProgram_EXTERNAL_OBJECTS =

AnotherProgram: CMakeFiles/AnotherProgram.dir/src/another_main.cpp.o
AnotherProgram: CMakeFiles/AnotherProgram.dir/build.make
AnotherProgram: libMyLibrary.a
AnotherProgram: CMakeFiles/AnotherProgram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AnotherProgram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnotherProgram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AnotherProgram.dir/build: AnotherProgram
.PHONY : CMakeFiles/AnotherProgram.dir/build

CMakeFiles/AnotherProgram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AnotherProgram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AnotherProgram.dir/clean

CMakeFiles/AnotherProgram.dir/depend:
	cd /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build /home/smkim/spatialai_slam_tutorial/_tutorial/01_cmake_ninja/build/CMakeFiles/AnotherProgram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AnotherProgram.dir/depend

