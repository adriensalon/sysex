cmake_minimum_required(VERSION 3.25.0)
project(midispec)

# midispec
file(GLOB_RECURSE midispec_source "source/*.cpp")
add_library(midispec STATIC ${midispec_source})
target_include_directories(midispec PUBLIC "include")
set_target_properties(midispec PROPERTIES CXX_STANDARD 17)

# midispec_test
set(BUILD_SHARED_LIBS OFF)
set(RTMIDI_BUILD_TESTING OFF)
add_subdirectory(external/rtmidi)
add_subdirectory(external/gtest)
add_library(midispec_test INTERFACE)
target_link_libraries(midispec_test INTERFACE midispec GTest::gtest_main rtmidi)
target_compile_definitions(midispec_test INTERFACE -DSYSEX_TEST_IN_MIDIPORT=0)
target_compile_definitions(midispec_test INTERFACE -DSYSEX_TEST_OUT_MIDIPORT=1)

# midispec_test [Akai MPX8]
add_executable(midispec_test_akai_mpx8 "test/test_akai_mpx8.cpp")
set_target_properties(midispec_test_akai_mpx8 PROPERTIES CXX_STANDARD 17)
target_link_libraries(midispec_test_akai_mpx8 PRIVATE midispec_test)

# midispec_test [Yamaha DX7]
add_executable(midispec_test_yamaha_dx7 "test/test_yamaha_dx7.cpp")
set_target_properties(midispec_test_yamaha_dx7 PROPERTIES CXX_STANDARD 17)
target_link_libraries(midispec_test_yamaha_dx7 PRIVATE midispec_test)

# midispec_test [Yamaha SPX90]
add_executable(midispec_test_yamaha_spx90 "test/test_yamaha_spx90.cpp")
set_target_properties(midispec_test_yamaha_spx90 PROPERTIES CXX_STANDARD 17)
target_link_libraries(midispec_test_yamaha_spx90 PRIVATE midispec_test)

# midispec_test [Yamaha TX81Z]
add_executable(midispec_test_yamaha_tx81z "test/test_yamaha_tx81z.cpp")
set_target_properties(midispec_test_yamaha_tx81z PROPERTIES CXX_STANDARD 17)
target_link_libraries(midispec_test_yamaha_tx81z PRIVATE midispec_test)