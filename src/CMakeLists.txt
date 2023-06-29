cmake_minimum_required(VERSION 3.12)
project(ExpenseTracker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)


# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

# Include directories
include_directories(${SQLITE3_INCLUDE_DIRS})

# Source files
set(SOURCES main.cc)

# Set output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Add the executable
add_executable(expense_tracker ${SOURCES})

# Link libraries
target_link_libraries(expense_tracker ${SQLITE3_LIBRARIES})
