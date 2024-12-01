cmake_minimum_required(VERSION 3.25)
project(ProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Core Core/Core.cpp)
target_include_directories(Core PUBLIC Include)

add_executable(ProjectName Source/Main.cpp)
target_link_libraries(ProjectName PRIVATE Core)

if(MSVC)
  target_compile_options(<target> PUBLIC "/ZI")
  target_link_options(<target> PUBLIC "/INCREMENTAL")
endif()

