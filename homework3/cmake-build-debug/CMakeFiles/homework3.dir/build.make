# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/homework3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/homework3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/homework3.dir/flags.make

CMakeFiles/homework3.dir/main.cpp.obj: CMakeFiles/homework3.dir/flags.make
CMakeFiles/homework3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/homework3.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\homework3.dir\main.cpp.obj -c "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\main.cpp"

CMakeFiles/homework3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/homework3.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\main.cpp" > CMakeFiles\homework3.dir\main.cpp.i

CMakeFiles/homework3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/homework3.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\main.cpp" -o CMakeFiles\homework3.dir\main.cpp.s

# Object files for target homework3
homework3_OBJECTS = \
"CMakeFiles/homework3.dir/main.cpp.obj"

# External object files for target homework3
homework3_EXTERNAL_OBJECTS =

homework3.exe: CMakeFiles/homework3.dir/main.cpp.obj
homework3.exe: CMakeFiles/homework3.dir/build.make
homework3.exe: CMakeFiles/homework3.dir/linklibs.rsp
homework3.exe: CMakeFiles/homework3.dir/objects1.rsp
homework3.exe: CMakeFiles/homework3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable homework3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\homework3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/homework3.dir/build: homework3.exe

.PHONY : CMakeFiles/homework3.dir/build

CMakeFiles/homework3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\homework3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/homework3.dir/clean

CMakeFiles/homework3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3" "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3" "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug" "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug" "C:\Labs\Y1S2\Proga (C++)\3\IS-2020-prog-2-sem\homework3\cmake-build-debug\CMakeFiles\homework3.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/homework3.dir/depend

