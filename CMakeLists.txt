cmake_minimum_required(VERSION 3.16)

project(ProcessManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

add_subdirectory(core)
add_subdirectory(application)

add_subdirectory(consoleApplication)
