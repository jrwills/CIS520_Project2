# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /opt/software/software/CMake/3.16.4-GCCcore-9.3.0/bin/cmake

# The command to remove a file.
RM = /opt/software/software/CMake/3.16.4-GCCcore-9.3.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/jrwills/p2/hw2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/jrwills/p2/hw2/build

# Include any dependencies generated for this target.
include CMakeFiles/analysis_exec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/analysis_exec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/analysis_exec.dir/flags.make

CMakeFiles/analysis_exec.dir/src/analysis.c.o: CMakeFiles/analysis_exec.dir/flags.make
CMakeFiles/analysis_exec.dir/src/analysis.c.o: ../src/analysis.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/jrwills/p2/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/analysis_exec.dir/src/analysis.c.o"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/analysis_exec.dir/src/analysis.c.o   -c /homes/jrwills/p2/hw2/src/analysis.c

CMakeFiles/analysis_exec.dir/src/analysis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/analysis_exec.dir/src/analysis.c.i"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/jrwills/p2/hw2/src/analysis.c > CMakeFiles/analysis_exec.dir/src/analysis.c.i

CMakeFiles/analysis_exec.dir/src/analysis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/analysis_exec.dir/src/analysis.c.s"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/jrwills/p2/hw2/src/analysis.c -o CMakeFiles/analysis_exec.dir/src/analysis.c.s

# Object files for target analysis_exec
analysis_exec_OBJECTS = \
"CMakeFiles/analysis_exec.dir/src/analysis.c.o"

# External object files for target analysis_exec
analysis_exec_EXTERNAL_OBJECTS =

analysis_exec: CMakeFiles/analysis_exec.dir/src/analysis.c.o
analysis_exec: CMakeFiles/analysis_exec.dir/build.make
analysis_exec: libdyn_array_lib.so
analysis_exec: CMakeFiles/analysis_exec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/jrwills/p2/hw2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable analysis_exec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/analysis_exec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/analysis_exec.dir/build: analysis_exec

.PHONY : CMakeFiles/analysis_exec.dir/build

CMakeFiles/analysis_exec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/analysis_exec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/analysis_exec.dir/clean

CMakeFiles/analysis_exec.dir/depend:
	cd /homes/jrwills/p2/hw2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/jrwills/p2/hw2 /homes/jrwills/p2/hw2 /homes/jrwills/p2/hw2/build /homes/jrwills/p2/hw2/build /homes/jrwills/p2/hw2/build/CMakeFiles/analysis_exec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/analysis_exec.dir/depend
