# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Jose\Desktop\bd2\bd2-lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/p3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/p3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p3.dir/flags.make

CMakeFiles/p3.dir/p3.cpp.obj: CMakeFiles/p3.dir/flags.make
CMakeFiles/p3.dir/p3.cpp.obj: ../p3.cpp
CMakeFiles/p3.dir/p3.cpp.obj: CMakeFiles/p3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p3.dir/p3.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/p3.dir/p3.cpp.obj -MF CMakeFiles\p3.dir\p3.cpp.obj.d -o CMakeFiles\p3.dir\p3.cpp.obj -c C:\Users\Jose\Desktop\bd2\bd2-lab1\p3.cpp

CMakeFiles/p3.dir/p3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p3.dir/p3.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Jose\Desktop\bd2\bd2-lab1\p3.cpp > CMakeFiles\p3.dir\p3.cpp.i

CMakeFiles/p3.dir/p3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p3.dir/p3.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Jose\Desktop\bd2\bd2-lab1\p3.cpp -o CMakeFiles\p3.dir\p3.cpp.s

# Object files for target p3
p3_OBJECTS = \
"CMakeFiles/p3.dir/p3.cpp.obj"

# External object files for target p3
p3_EXTERNAL_OBJECTS =

p3.exe: CMakeFiles/p3.dir/p3.cpp.obj
p3.exe: CMakeFiles/p3.dir/build.make
p3.exe: CMakeFiles/p3.dir/linklibs.rsp
p3.exe: CMakeFiles/p3.dir/objects1.rsp
p3.exe: CMakeFiles/p3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p3.dir/build: p3.exe
.PHONY : CMakeFiles/p3.dir/build

CMakeFiles/p3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\p3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/p3.dir/clean

CMakeFiles/p3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Jose\Desktop\bd2\bd2-lab1 C:\Users\Jose\Desktop\bd2\bd2-lab1 C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug C:\Users\Jose\Desktop\bd2\bd2-lab1\cmake-build-debug\CMakeFiles\p3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p3.dir/depend

