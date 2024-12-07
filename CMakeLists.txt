cmake_minimum_required(VERSION 3.25)
project(ProjectName)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Core Core/Core.cpp)
target_include_directories(Core PUBLIC Include)

if(MSVC)
  target_compile_options(<target> PUBLIC "/ZI")
  target_link_options(<target> PUBLIC "/INCREMENTAL")
endif()

function (AddDay DAY_NUMBER)
  add_executable(day${DAY_NUMBER} ${SOURCE} Source/day${DAY_NUMBER}/main.cc)
  target_link_libraries(day${DAY_NUMBER} PRIVATE Core)
endfunction()

AddDay(01)
AddDay(02)
AddDay(03)
AddDay(04)
AddDay(05)
AddDay(06)
AddDay(07)
