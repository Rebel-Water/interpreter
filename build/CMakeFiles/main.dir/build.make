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
CMAKE_SOURCE_DIR = /home/ace/interpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ace/interpreter/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/value.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/value.cpp.o: ../src/value.cpp
CMakeFiles/main.dir/src/value.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/value.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/value.cpp.o -MF CMakeFiles/main.dir/src/value.cpp.o.d -o CMakeFiles/main.dir/src/value.cpp.o -c /home/ace/interpreter/src/value.cpp

CMakeFiles/main.dir/src/value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/value.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/value.cpp > CMakeFiles/main.dir/src/value.cpp.i

CMakeFiles/main.dir/src/value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/value.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/value.cpp -o CMakeFiles/main.dir/src/value.cpp.s

CMakeFiles/main.dir/src/objstring.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/objstring.cpp.o: ../src/objstring.cpp
CMakeFiles/main.dir/src/objstring.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/objstring.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/objstring.cpp.o -MF CMakeFiles/main.dir/src/objstring.cpp.o.d -o CMakeFiles/main.dir/src/objstring.cpp.o -c /home/ace/interpreter/src/objstring.cpp

CMakeFiles/main.dir/src/objstring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/objstring.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/objstring.cpp > CMakeFiles/main.dir/src/objstring.cpp.i

CMakeFiles/main.dir/src/objstring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/objstring.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/objstring.cpp -o CMakeFiles/main.dir/src/objstring.cpp.s

CMakeFiles/main.dir/src/object.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/object.cpp.o: ../src/object.cpp
CMakeFiles/main.dir/src/object.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/object.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/object.cpp.o -MF CMakeFiles/main.dir/src/object.cpp.o.d -o CMakeFiles/main.dir/src/object.cpp.o -c /home/ace/interpreter/src/object.cpp

CMakeFiles/main.dir/src/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/object.cpp > CMakeFiles/main.dir/src/object.cpp.i

CMakeFiles/main.dir/src/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/object.cpp -o CMakeFiles/main.dir/src/object.cpp.s

CMakeFiles/main.dir/src/memory.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/memory.cpp.o: ../src/memory.cpp
CMakeFiles/main.dir/src/memory.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/memory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/memory.cpp.o -MF CMakeFiles/main.dir/src/memory.cpp.o.d -o CMakeFiles/main.dir/src/memory.cpp.o -c /home/ace/interpreter/src/memory.cpp

CMakeFiles/main.dir/src/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/memory.cpp > CMakeFiles/main.dir/src/memory.cpp.i

CMakeFiles/main.dir/src/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/memory.cpp -o CMakeFiles/main.dir/src/memory.cpp.s

CMakeFiles/main.dir/src/util.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/util.cpp.o: ../src/util.cpp
CMakeFiles/main.dir/src/util.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/util.cpp.o -MF CMakeFiles/main.dir/src/util.cpp.o.d -o CMakeFiles/main.dir/src/util.cpp.o -c /home/ace/interpreter/src/util.cpp

CMakeFiles/main.dir/src/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/util.cpp > CMakeFiles/main.dir/src/util.cpp.i

CMakeFiles/main.dir/src/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/util.cpp -o CMakeFiles/main.dir/src/util.cpp.s

CMakeFiles/main.dir/src/scanner.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/scanner.cpp.o: ../src/scanner.cpp
CMakeFiles/main.dir/src/scanner.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/scanner.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/scanner.cpp.o -MF CMakeFiles/main.dir/src/scanner.cpp.o.d -o CMakeFiles/main.dir/src/scanner.cpp.o -c /home/ace/interpreter/src/scanner.cpp

CMakeFiles/main.dir/src/scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/scanner.cpp > CMakeFiles/main.dir/src/scanner.cpp.i

CMakeFiles/main.dir/src/scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/scanner.cpp -o CMakeFiles/main.dir/src/scanner.cpp.s

CMakeFiles/main.dir/src/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser.cpp.o: ../src/parser.cpp
CMakeFiles/main.dir/src/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/src/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser.cpp.o -MF CMakeFiles/main.dir/src/parser.cpp.o.d -o CMakeFiles/main.dir/src/parser.cpp.o -c /home/ace/interpreter/src/parser.cpp

CMakeFiles/main.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/parser.cpp > CMakeFiles/main.dir/src/parser.cpp.i

CMakeFiles/main.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/parser.cpp -o CMakeFiles/main.dir/src/parser.cpp.s

CMakeFiles/main.dir/src/compiler.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/compiler.cpp.o: ../src/compiler.cpp
CMakeFiles/main.dir/src/compiler.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/src/compiler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/compiler.cpp.o -MF CMakeFiles/main.dir/src/compiler.cpp.o.d -o CMakeFiles/main.dir/src/compiler.cpp.o -c /home/ace/interpreter/src/compiler.cpp

CMakeFiles/main.dir/src/compiler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/compiler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/compiler.cpp > CMakeFiles/main.dir/src/compiler.cpp.i

CMakeFiles/main.dir/src/compiler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/compiler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/compiler.cpp -o CMakeFiles/main.dir/src/compiler.cpp.s

CMakeFiles/main.dir/src/vm.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/vm.cpp.o: ../src/vm.cpp
CMakeFiles/main.dir/src/vm.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/src/vm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/vm.cpp.o -MF CMakeFiles/main.dir/src/vm.cpp.o.d -o CMakeFiles/main.dir/src/vm.cpp.o -c /home/ace/interpreter/src/vm.cpp

CMakeFiles/main.dir/src/vm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/vm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/vm.cpp > CMakeFiles/main.dir/src/vm.cpp.i

CMakeFiles/main.dir/src/vm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/vm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/vm.cpp -o CMakeFiles/main.dir/src/vm.cpp.s

CMakeFiles/main.dir/src/chunk.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/chunk.cpp.o: ../src/chunk.cpp
CMakeFiles/main.dir/src/chunk.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/src/chunk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/chunk.cpp.o -MF CMakeFiles/main.dir/src/chunk.cpp.o.d -o CMakeFiles/main.dir/src/chunk.cpp.o -c /home/ace/interpreter/src/chunk.cpp

CMakeFiles/main.dir/src/chunk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/chunk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/src/chunk.cpp > CMakeFiles/main.dir/src/chunk.cpp.i

CMakeFiles/main.dir/src/chunk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/chunk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/src/chunk.cpp -o CMakeFiles/main.dir/src/chunk.cpp.s

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /home/ace/interpreter/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ace/interpreter/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ace/interpreter/main.cpp -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/value.cpp.o" \
"CMakeFiles/main.dir/src/objstring.cpp.o" \
"CMakeFiles/main.dir/src/object.cpp.o" \
"CMakeFiles/main.dir/src/memory.cpp.o" \
"CMakeFiles/main.dir/src/util.cpp.o" \
"CMakeFiles/main.dir/src/scanner.cpp.o" \
"CMakeFiles/main.dir/src/parser.cpp.o" \
"CMakeFiles/main.dir/src/compiler.cpp.o" \
"CMakeFiles/main.dir/src/vm.cpp.o" \
"CMakeFiles/main.dir/src/chunk.cpp.o" \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/value.cpp.o
main: CMakeFiles/main.dir/src/objstring.cpp.o
main: CMakeFiles/main.dir/src/object.cpp.o
main: CMakeFiles/main.dir/src/memory.cpp.o
main: CMakeFiles/main.dir/src/util.cpp.o
main: CMakeFiles/main.dir/src/scanner.cpp.o
main: CMakeFiles/main.dir/src/parser.cpp.o
main: CMakeFiles/main.dir/src/compiler.cpp.o
main: CMakeFiles/main.dir/src/vm.cpp.o
main: CMakeFiles/main.dir/src/chunk.cpp.o
main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ace/interpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ace/interpreter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ace/interpreter /home/ace/interpreter /home/ace/interpreter/build /home/ace/interpreter/build /home/ace/interpreter/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

