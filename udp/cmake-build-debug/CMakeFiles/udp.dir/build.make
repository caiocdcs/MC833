# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/udp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/udp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/udp.dir/flags.make

CMakeFiles/udp.dir/controller.c.o: CMakeFiles/udp.dir/flags.make
CMakeFiles/udp.dir/controller.c.o: ../controller.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/udp.dir/controller.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/udp.dir/controller.c.o   -c /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/controller.c

CMakeFiles/udp.dir/controller.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udp.dir/controller.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/controller.c > CMakeFiles/udp.dir/controller.c.i

CMakeFiles/udp.dir/controller.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udp.dir/controller.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/controller.c -o CMakeFiles/udp.dir/controller.c.s

CMakeFiles/udp.dir/database.c.o: CMakeFiles/udp.dir/flags.make
CMakeFiles/udp.dir/database.c.o: ../database.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/udp.dir/database.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/udp.dir/database.c.o   -c /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/database.c

CMakeFiles/udp.dir/database.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udp.dir/database.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/database.c > CMakeFiles/udp.dir/database.c.i

CMakeFiles/udp.dir/database.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udp.dir/database.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/database.c -o CMakeFiles/udp.dir/database.c.s

CMakeFiles/udp.dir/server.c.o: CMakeFiles/udp.dir/flags.make
CMakeFiles/udp.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/udp.dir/server.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/udp.dir/server.c.o   -c /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/server.c

CMakeFiles/udp.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udp.dir/server.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/server.c > CMakeFiles/udp.dir/server.c.i

CMakeFiles/udp.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udp.dir/server.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/server.c -o CMakeFiles/udp.dir/server.c.s

CMakeFiles/udp.dir/services.c.o: CMakeFiles/udp.dir/flags.make
CMakeFiles/udp.dir/services.c.o: ../services.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/udp.dir/services.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/udp.dir/services.c.o   -c /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/services.c

CMakeFiles/udp.dir/services.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/udp.dir/services.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/services.c > CMakeFiles/udp.dir/services.c.i

CMakeFiles/udp.dir/services.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/udp.dir/services.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/services.c -o CMakeFiles/udp.dir/services.c.s

# Object files for target udp
udp_OBJECTS = \
"CMakeFiles/udp.dir/controller.c.o" \
"CMakeFiles/udp.dir/database.c.o" \
"CMakeFiles/udp.dir/server.c.o" \
"CMakeFiles/udp.dir/services.c.o"

# External object files for target udp
udp_EXTERNAL_OBJECTS =

udp: CMakeFiles/udp.dir/controller.c.o
udp: CMakeFiles/udp.dir/database.c.o
udp: CMakeFiles/udp.dir/server.c.o
udp: CMakeFiles/udp.dir/services.c.o
udp: CMakeFiles/udp.dir/build.make
udp: CMakeFiles/udp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable udp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/udp.dir/build: udp

.PHONY : CMakeFiles/udp.dir/build

CMakeFiles/udp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/udp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/udp.dir/clean

CMakeFiles/udp.dir/depend:
	cd /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug /Users/caio.cesar/workspace/unicamp/mc833/MC833/udp/cmake-build-debug/CMakeFiles/udp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/udp.dir/depend

