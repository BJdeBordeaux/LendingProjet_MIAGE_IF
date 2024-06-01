cmake_minimum_required(VERSION 3.27)
project(lendingProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to the MySQL Connector/C++ installation
set(MYSQL_CONNECTOR_CPP_INCLUDE_DIR "C://Users//qq870//Desktop//tools//mysql-connector-c++-8.4.0-winx64//include")
set(MYSQL_CONNECTOR_CPP_LIBRARY_DIR "C://Users//qq870//Desktop//tools//mysql-connector-c++-8.4.0-winx64//lib64")
set(CMAKE_SOURCE_DIR "C://Users//qq870//Desktop//tools//mysql-connector-c++-8.4.0-winx64")

# Add the path to the CMake module for MySQL Connector/C++
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Include directories
include_directories(${MYSQL_CONNECTOR_CPP_INCLUDE_DIR})
include_directories(${MYSQL_CONNECTOR_CPP_INCLUDE_DIR}/jdbc)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Link directories
link_directories(${MYSQL_CONNECTOR_CPP_LIBRARY_DIR})

## Find MySQL Connector/C++ package
#find_package(MySQL REQUIRED)

include_directories("C://Users//qq870//Desktop//tools//mysql-connector-c++-8.4.0-winx64//include")
link_directories("C://Users//qq870//Desktop//tools//mysql-connector-c++-8.4.0-winx64//lib64")


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
        src/utils/Utils.cpp
        src/utils/Utils.h
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(Account src/tests/testAccount.cpp src/Account.cpp src/utils/Utils.cpp)
add_executable(Facility src/Facility.cpp src/utils/Utils.cpp src/Part.cpp
        src/tests/testFacility.cpp)
add_executable(Portfolio src/tests/testPortfolio.cpp src/Portfolio.cpp src/Facility.cpp src/utils/Utils.cpp src/Account.cpp
        src/Part.cpp)
add_executable(Borrower src/Borrower.cpp src/utils/Utils.cpp src/Account.cpp
        src/tests/testBorrower.cpp)
add_executable(Lender src/Lender.cpp src/Portfolio.cpp src/Facility.cpp src/utils/Utils.cpp src/Account.cpp
        src/tests/testLender.cpp src/Part.cpp)
add_executable(Deal src/Deal.cpp src/Lender.cpp src/Portfolio.cpp src/Facility.cpp src/utils/Utils.cpp src/Account.cpp
        src/tests/testDeal.cpp src/Part.cpp)
add_executable(Part src/tests/testPart.cpp src/Part.cpp src/utils/Utils.cpp)
add_executable(Utils src/utils/Utils.cpp src/tests/testUtils.cpp)
