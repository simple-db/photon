cmake_minimum_required(VERSION 3.2)

project (photon)

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CPP_FLAGS}-pipe -Wall -W -fPIC -fstrict-aliasing -Wno-invalid-offsetof -Wno-unused-parameter -fno-omit-frame-pointer")

include_directories(./src ./idl)
aux_source_directory(./src SRCS)
aux_source_directory(./cli CLIS)
aux_source_directory(./idl IDL)

add_subdirectory(unittest)

link_libraries(braft brpc protobuf gflags leveldb pthread ssl crypto dl rt)

add_definitions(-std=c++17 -static)

add_executable(photon ${SRCS} ${IDL})
add_executable(pcli ${CLIS} ${IDL})

