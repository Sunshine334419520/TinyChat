# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sunshine/Code/C++/TinyChat/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TinyChatServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TinyChatServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TinyChatServer.dir/flags.make

CMakeFiles/TinyChatServer.dir/thread/thread.cc.o: CMakeFiles/TinyChatServer.dir/flags.make
CMakeFiles/TinyChatServer.dir/thread/thread.cc.o: ../thread/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TinyChatServer.dir/thread/thread.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TinyChatServer.dir/thread/thread.cc.o -c /Users/sunshine/Code/C++/TinyChat/server/thread/thread.cc

CMakeFiles/TinyChatServer.dir/thread/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TinyChatServer.dir/thread/thread.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sunshine/Code/C++/TinyChat/server/thread/thread.cc > CMakeFiles/TinyChatServer.dir/thread/thread.cc.i

CMakeFiles/TinyChatServer.dir/thread/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TinyChatServer.dir/thread/thread.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sunshine/Code/C++/TinyChat/server/thread/thread.cc -o CMakeFiles/TinyChatServer.dir/thread/thread.cc.s

CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.requires:

.PHONY : CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.requires

CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.provides: CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.requires
	$(MAKE) -f CMakeFiles/TinyChatServer.dir/build.make CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.provides.build
.PHONY : CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.provides

CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.provides.build: CMakeFiles/TinyChatServer.dir/thread/thread.cc.o


CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o: CMakeFiles/TinyChatServer.dir/flags.make
CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o: ../thread/thread_pool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o -c /Users/sunshine/Code/C++/TinyChat/server/thread/thread_pool.cc

CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sunshine/Code/C++/TinyChat/server/thread/thread_pool.cc > CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.i

CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sunshine/Code/C++/TinyChat/server/thread/thread_pool.cc -o CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.s

CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.requires:

.PHONY : CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.requires

CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.provides: CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.requires
	$(MAKE) -f CMakeFiles/TinyChatServer.dir/build.make CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.provides.build
.PHONY : CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.provides

CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.provides.build: CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o


CMakeFiles/TinyChatServer.dir/thread/lock.cc.o: CMakeFiles/TinyChatServer.dir/flags.make
CMakeFiles/TinyChatServer.dir/thread/lock.cc.o: ../thread/lock.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TinyChatServer.dir/thread/lock.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TinyChatServer.dir/thread/lock.cc.o -c /Users/sunshine/Code/C++/TinyChat/server/thread/lock.cc

CMakeFiles/TinyChatServer.dir/thread/lock.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TinyChatServer.dir/thread/lock.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sunshine/Code/C++/TinyChat/server/thread/lock.cc > CMakeFiles/TinyChatServer.dir/thread/lock.cc.i

CMakeFiles/TinyChatServer.dir/thread/lock.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TinyChatServer.dir/thread/lock.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sunshine/Code/C++/TinyChat/server/thread/lock.cc -o CMakeFiles/TinyChatServer.dir/thread/lock.cc.s

CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.requires:

.PHONY : CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.requires

CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.provides: CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.requires
	$(MAKE) -f CMakeFiles/TinyChatServer.dir/build.make CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.provides.build
.PHONY : CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.provides

CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.provides.build: CMakeFiles/TinyChatServer.dir/thread/lock.cc.o


CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o: CMakeFiles/TinyChatServer.dir/flags.make
CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o: ../thread/tiny_chat_thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o -c /Users/sunshine/Code/C++/TinyChat/server/thread/tiny_chat_thread.cc

CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sunshine/Code/C++/TinyChat/server/thread/tiny_chat_thread.cc > CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.i

CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sunshine/Code/C++/TinyChat/server/thread/tiny_chat_thread.cc -o CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.s

CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.requires:

.PHONY : CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.requires

CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.provides: CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.requires
	$(MAKE) -f CMakeFiles/TinyChatServer.dir/build.make CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.provides.build
.PHONY : CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.provides

CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.provides.build: CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o


CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o: CMakeFiles/TinyChatServer.dir/flags.make
CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o: ../tiny_chat_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o -c /Users/sunshine/Code/C++/TinyChat/server/tiny_chat_main.cc

CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sunshine/Code/C++/TinyChat/server/tiny_chat_main.cc > CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.i

CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sunshine/Code/C++/TinyChat/server/tiny_chat_main.cc -o CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.s

CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.requires:

.PHONY : CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.requires

CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.provides: CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.requires
	$(MAKE) -f CMakeFiles/TinyChatServer.dir/build.make CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.provides.build
.PHONY : CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.provides

CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.provides.build: CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o


# Object files for target TinyChatServer
TinyChatServer_OBJECTS = \
"CMakeFiles/TinyChatServer.dir/thread/thread.cc.o" \
"CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o" \
"CMakeFiles/TinyChatServer.dir/thread/lock.cc.o" \
"CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o" \
"CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o"

# External object files for target TinyChatServer
TinyChatServer_EXTERNAL_OBJECTS =

TinyChatServer: CMakeFiles/TinyChatServer.dir/thread/thread.cc.o
TinyChatServer: CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o
TinyChatServer: CMakeFiles/TinyChatServer.dir/thread/lock.cc.o
TinyChatServer: CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o
TinyChatServer: CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o
TinyChatServer: CMakeFiles/TinyChatServer.dir/build.make
TinyChatServer: CMakeFiles/TinyChatServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable TinyChatServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TinyChatServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TinyChatServer.dir/build: TinyChatServer

.PHONY : CMakeFiles/TinyChatServer.dir/build

CMakeFiles/TinyChatServer.dir/requires: CMakeFiles/TinyChatServer.dir/thread/thread.cc.o.requires
CMakeFiles/TinyChatServer.dir/requires: CMakeFiles/TinyChatServer.dir/thread/thread_pool.cc.o.requires
CMakeFiles/TinyChatServer.dir/requires: CMakeFiles/TinyChatServer.dir/thread/lock.cc.o.requires
CMakeFiles/TinyChatServer.dir/requires: CMakeFiles/TinyChatServer.dir/thread/tiny_chat_thread.cc.o.requires
CMakeFiles/TinyChatServer.dir/requires: CMakeFiles/TinyChatServer.dir/tiny_chat_main.cc.o.requires

.PHONY : CMakeFiles/TinyChatServer.dir/requires

CMakeFiles/TinyChatServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TinyChatServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TinyChatServer.dir/clean

CMakeFiles/TinyChatServer.dir/depend:
	cd /Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sunshine/Code/C++/TinyChat/server /Users/sunshine/Code/C++/TinyChat/server /Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug /Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug /Users/sunshine/Code/C++/TinyChat/server/cmake-build-debug/CMakeFiles/TinyChatServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TinyChatServer.dir/depend

