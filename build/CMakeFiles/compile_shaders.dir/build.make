# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/ixilminiussi/Desktop/gamedev/vulkan-engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ixilminiussi/Desktop/gamedev/vulkan-engine/build

# Utility rule file for compile_shaders.

# Include any custom commands dependencies for this target.
include CMakeFiles/compile_shaders.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compile_shaders.dir/progress.make

CMakeFiles/compile_shaders:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/ixilminiussi/Desktop/gamedev/vulkan-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Compiling shaders..."
	bash /home/ixilminiussi/Desktop/gamedev/vulkan-engine/compile.sh

compile_shaders: CMakeFiles/compile_shaders
compile_shaders: CMakeFiles/compile_shaders.dir/build.make
.PHONY : compile_shaders

# Rule to build all files generated by this target.
CMakeFiles/compile_shaders.dir/build: compile_shaders
.PHONY : CMakeFiles/compile_shaders.dir/build

CMakeFiles/compile_shaders.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compile_shaders.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compile_shaders.dir/clean

CMakeFiles/compile_shaders.dir/depend:
	cd /home/ixilminiussi/Desktop/gamedev/vulkan-engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ixilminiussi/Desktop/gamedev/vulkan-engine /home/ixilminiussi/Desktop/gamedev/vulkan-engine /home/ixilminiussi/Desktop/gamedev/vulkan-engine/build /home/ixilminiussi/Desktop/gamedev/vulkan-engine/build /home/ixilminiussi/Desktop/gamedev/vulkan-engine/build/CMakeFiles/compile_shaders.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/compile_shaders.dir/depend
