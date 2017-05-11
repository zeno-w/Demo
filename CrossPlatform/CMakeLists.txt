cmake_minimum_required(VERSION 3.7)
project(CrossPlatform)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp cxx11_new_feature/ObjectCunstructionImprovement.cpp)

include_directories(G:/Fayne/ZZExtraLibs/googletest/original_repo/googletest/include)
link_directories(G:/Fayne/ZZExtraLibs/googletest/original_repo/googletest/cmake-build-debug)

add_executable(CrossPlatform ${SOURCE_FILES})

target_link_libraries(CrossPlatform gtest)