# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build

# Utility rule file for uninstall.

# Include the progress variables for this target.
include CMakeFiles/uninstall.dir/progress.make

CMakeFiles/uninstall:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "uninstall ComponentFaceDetection"
	/usr/bin/cmake -P /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build/cmake_uninstall.cmake

uninstall: CMakeFiles/uninstall
uninstall: CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
CMakeFiles/uninstall.dir/build: uninstall

.PHONY : CMakeFiles/uninstall.dir/build

CMakeFiles/uninstall.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uninstall.dir/clean

CMakeFiles/uninstall.dir/depend:
	cd /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build /home/rosmosys/SOFTWARE/smartsoft-ace-mdsd-v3/repos/workspace/ComponentFaceDetection/smartsoft/build/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uninstall.dir/depend

