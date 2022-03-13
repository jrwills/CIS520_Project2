cmake_minimum_required(VERSION 2.8)

# ALL OF THE SPECIFIED NAMES IN THIS CMAKE ARE REQUIRED.
# Set the project name variable to assignment3.
# THIS IS REQUIRED
project(hw2)

# Add your CMAKE_C_FLAGS AND CMAKE_CXX_FLAGS here
# Make SURE to use -std=c11 and -std=c++11 where relevant.
# The options specified below are required, but additional options
#  may be used.
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")

# Add our include directory to CMake's search paths.
# THIS IS REQUIRED ME V
include_directories(hw2 ./include)

# Create library from dyn_array so we can use it later. ME V
add_library(dyn_array_lib SHARED src/dyn_array.c)
add_library(process_scheduling_lib SHARED src/process_scheduling.c)

# Compile the analysis executable. ME x 2 V
add_executable(analysis_exec src/analysis.c)
target_compile_definitions(analysis_exec PRIVATE)

# link the dyn_array library we compiled against our analysis executable. ME V
target_link_libraries(analysis_exec dyn_array_lib process_scheduling_lib)

# Compile the the tester executable. //edit
add_executable(hw2_test test/tests.cpp src/process_scheduling.c)
target_compile_definitions(hw2_test PRIVATE)

# Link ${PROJECT_NAME}_test with dyn_array and gtest and pthread libraries //edit
target_link_libraries(hw2_test gtest pthread dyn_array_lib)
#target_link_libraries(hw2_test gtest pthread process_scheduling_lib)
