cmake_minimum_required(VERSION 3.27)
project(lendingProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the path to the MySQL CMake configuration files
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/path/to/mysql/")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#find_package(MySQL REQUIRED)
#find_package(mysqlclient REQUIRED)
#include_directories(${MySQL_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${MySQL_LIBRARIES})


# Include directories
include_directories(.)
include_directories(src)

# Add source files
set(SOURCE_FILES
        src/main.cpp
        src/Deal.cpp
        src/Deal.h
        src/Facility.cpp
        src/Facility.h
        src/Part.cpp
        src/Part.h
        src/Portfolio.cpp
        src/Portfolio.h
        src/Borrower.cpp
        src/Borrower.h
        src/Lender.cpp
        src/Lender.h
        src/Account.cpp
        src/Account.h
#        src/Database.cpp
#        src/Database.h
        src/utils/Utils.cpp
        src/utils/Utils.h
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

## Include directories for Google Test
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
#)
#FetchContent_MakeAvailable(googletest)
#
#enable_testing()
#add_subdirectory(tests)
#
## Link Google Test libraries
#target_link_libraries(${PROJECT_NAME} gtest gtest_main)
