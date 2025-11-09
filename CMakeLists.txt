cmake_minimum_required(VERSION 3.25.0)
project(sysex)

# sysex
file(GLOB_RECURSE sysex_source "source/*.cpp")
add_library(sysex STATIC ${sysex_source})
target_include_directories(sysex PUBLIC "include")
set_target_properties(sysex PROPERTIES CXX_STANDARD 17)

# sysex_test
set(BUILD_SHARED_LIBS OFF)
set(RTMIDI_BUILD_TESTING OFF)
add_subdirectory(external/rtmidi)
add_subdirectory(external/gtest)
add_library(sysex_test INTERFACE)
target_link_libraries(sysex_test INTERFACE sysex GTest::gtest_main rtmidi)
target_compile_definitions(sysex_test INTERFACE -DSYSEX_TEST_IN_MIDIPORT=0)
target_compile_definitions(sysex_test INTERFACE -DSYSEX_TEST_OUT_MIDIPORT=1)

# sysex_test [yamaha dx7]
add_executable(sysex_test_yamaha_dx7 "test/test_yamaha_dx7.cpp")
set_target_properties(sysex_test_yamaha_dx7 PROPERTIES CXX_STANDARD 17)
target_link_libraries(sysex_test_yamaha_dx7 PRIVATE sysex_test)