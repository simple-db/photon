cmake_minimum_required(VERSION 2.8)

project (photon)

include_directories(./src ./idl)

aux_source_directory(./src SRCS)
aux_source_directory(./idl IDL)

link_libraries(brpc protobuf gflags leveldb pthread ssl crypto dl rt)

add_definitions(-std=c++11 -static)

add_executable(photon ${SRCS} ${IDL})

add_custom_target(output command echo "hello")
