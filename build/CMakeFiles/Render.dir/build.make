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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/percy/Projects/graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/percy/Projects/graphics/build

# Include any dependencies generated for this target.
include CMakeFiles/Render.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Render.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Render.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Render.dir/flags.make

CMakeFiles/Render.dir/src/main.cpp.o: CMakeFiles/Render.dir/flags.make
CMakeFiles/Render.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/Render.dir/src/main.cpp.o: CMakeFiles/Render.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/percy/Projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Render.dir/src/main.cpp.o"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Render.dir/src/main.cpp.o -MF CMakeFiles/Render.dir/src/main.cpp.o.d -o CMakeFiles/Render.dir/src/main.cpp.o -c /home/percy/Projects/graphics/src/main.cpp

CMakeFiles/Render.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Render.dir/src/main.cpp.i"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/percy/Projects/graphics/src/main.cpp > CMakeFiles/Render.dir/src/main.cpp.i

CMakeFiles/Render.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Render.dir/src/main.cpp.s"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/percy/Projects/graphics/src/main.cpp -o CMakeFiles/Render.dir/src/main.cpp.s

CMakeFiles/Render.dir/src/Window/Window.cpp.o: CMakeFiles/Render.dir/flags.make
CMakeFiles/Render.dir/src/Window/Window.cpp.o: ../src/Window/Window.cpp
CMakeFiles/Render.dir/src/Window/Window.cpp.o: CMakeFiles/Render.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/percy/Projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Render.dir/src/Window/Window.cpp.o"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Render.dir/src/Window/Window.cpp.o -MF CMakeFiles/Render.dir/src/Window/Window.cpp.o.d -o CMakeFiles/Render.dir/src/Window/Window.cpp.o -c /home/percy/Projects/graphics/src/Window/Window.cpp

CMakeFiles/Render.dir/src/Window/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Render.dir/src/Window/Window.cpp.i"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/percy/Projects/graphics/src/Window/Window.cpp > CMakeFiles/Render.dir/src/Window/Window.cpp.i

CMakeFiles/Render.dir/src/Window/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Render.dir/src/Window/Window.cpp.s"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/percy/Projects/graphics/src/Window/Window.cpp -o CMakeFiles/Render.dir/src/Window/Window.cpp.s

CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o: CMakeFiles/Render.dir/flags.make
CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o: ../src/Window/Mouse/Mouse.cpp
CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o: CMakeFiles/Render.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/percy/Projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o -MF CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o.d -o CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o -c /home/percy/Projects/graphics/src/Window/Mouse/Mouse.cpp

CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.i"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/percy/Projects/graphics/src/Window/Mouse/Mouse.cpp > CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.i

CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.s"
	/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/percy/Projects/graphics/src/Window/Mouse/Mouse.cpp -o CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.s

# Object files for target Render
Render_OBJECTS = \
"CMakeFiles/Render.dir/src/main.cpp.o" \
"CMakeFiles/Render.dir/src/Window/Window.cpp.o" \
"CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o"

# External object files for target Render
Render_EXTERNAL_OBJECTS =

Render: CMakeFiles/Render.dir/src/main.cpp.o
Render: CMakeFiles/Render.dir/src/Window/Window.cpp.o
Render: CMakeFiles/Render.dir/src/Window/Mouse/Mouse.cpp.o
Render: CMakeFiles/Render.dir/build.make
Render: /opt/vcpkg/installed/x64-linux/debug/lib/libglad.a
Render: /opt/vcpkg/installed/x64-linux/debug/lib/libglfw3.a
Render: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.8.1
Render: /usr/lib/x86_64-linux-gnu/librt.so
Render: /usr/lib/x86_64-linux-gnu/libm.so
Render: /usr/lib/x86_64-linux-gnu/libX11.so
Render: /usr/lib/x86_64-linux-gnu/libfmt.so.7.1.3
Render: CMakeFiles/Render.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/percy/Projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Render"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Render.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Render.dir/build: Render
.PHONY : CMakeFiles/Render.dir/build

CMakeFiles/Render.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Render.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Render.dir/clean

CMakeFiles/Render.dir/depend:
	cd /home/percy/Projects/graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/percy/Projects/graphics /home/percy/Projects/graphics /home/percy/Projects/graphics/build /home/percy/Projects/graphics/build /home/percy/Projects/graphics/build/CMakeFiles/Render.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Render.dir/depend
