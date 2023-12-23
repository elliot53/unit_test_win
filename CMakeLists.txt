cmake_minimum_required(VERSION 3.10)
project(unit_test_win)

include_directories(${CMAKE_SOURCE_DIR}/headers/)

aux_source_directory(${CMAKE_SOURCE_DIR}/source/ src_file_array)
message(${src_file_array})

add_executable(unit_test_win ${src_file_array})

target_link_libraries(unit_test_win Ws2_32.lib)