cmake_minimum_required(VERSION 3.25.0)
project(midispec VERSION 0.0.1)

option(MIDISPEC_BUILD_GTEST "Build midispec GTest testing executables" ON)
option(MIDISPEC_BOUND_CHECK "Build midispec bounds checking" ON)

file(GLOB_RECURSE midispec_source "source/*.cpp")
add_library(midispec STATIC ${midispec_source})
target_include_directories(midispec PUBLIC "include")
set_target_properties(midispec PROPERTIES CXX_STANDARD 17)
if(MIDISPEC_BOUND_CHECK)
    target_compile_definitions(midispec PUBLIC -DMIDISPEC_BOUND_CHECK)
endif()

if(MIDISPEC_BUILD_GTEST)
    set(BUILD_SHARED_LIBS OFF)
    set(RTMIDI_BUILD_TESTING OFF)
    add_subdirectory(external/rtmidi)
    add_subdirectory(external/gtest)
    target_link_libraries(midispec PUBLIC rtmidi GTest::gtest_main)

    # midispec_test [Akai LPK25]
    add_executable(midispec_gtest_akai_lpk25 "test/gtest_akai_lpk25.cpp")
    set_target_properties(midispec_gtest_akai_lpk25 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_akai_lpk25 PRIVATE midispec)

    # midispec_test [Akai MPX8]
    add_executable(midispec_gtest_akai_mpx8 "test/gtest_akai_mpx8.cpp")
    set_target_properties(midispec_gtest_akai_mpx8 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_akai_mpx8 PRIVATE midispec)

    # midispec_test [Yamaha DX7]
    add_executable(midispec_gtest_yamaha_dx7 "test/gtest_yamaha_dx7.cpp")
    set_target_properties(midispec_gtest_yamaha_dx7 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_dx7 PRIVATE midispec)

    # midispec_test [Yamaha SPX90]
    add_executable(midispec_gtest_yamaha_spx90 "test/gtest_yamaha_spx90.cpp")
    set_target_properties(midispec_gtest_yamaha_spx90 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_spx90 PRIVATE midispec)

    # midispec_test [Yamaha TX81Z]
    add_executable(midispec_gtest_yamaha_tx81z "test/gtest_yamaha_tx81z.cpp")
    set_target_properties(midispec_gtest_yamaha_tx81z PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_tx81z PRIVATE midispec)

endif()
