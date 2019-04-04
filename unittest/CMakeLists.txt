cmake_minimum_required(VERSION 3.2)

project (photon_test)

add_definitions(-std=c++17)

aux_source_directory(../idl ORI_IDL)
aux_source_directory(../src ORI_SRCS)
aux_source_directory(. TEST_SRCS)

link_libraries(braft brpc protobuf gflags leveldb pthread ssl crypto dl rt)

ADD_DEFINITIONS(-D__UNITTEST__ -DFMT_HEADER_ONLY)

add_executable(test_table ${TEST_SRCS} ${ORI_SRCS} ${ORI_IDL})

target_link_libraries(test_table gtest gtest_main)
