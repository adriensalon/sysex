cmake_minimum_required(VERSION 3.25.0)
project(midispec)

option(MIDISPEC_BUILD_GTEST "Build midispec GTest testing executables" ON)
option(MIDISPEC_BUILD_VST3 "Build midispec VST3 testing editor modules" ON)
option(MIDISPEC_BUILD_STANDALONE "Build midispec standalone testing editor executables" ON)

file(GLOB_RECURSE midispec_source "source/*.cpp")
add_library(midispec STATIC ${midispec_source})
target_include_directories(midispec PUBLIC "include")
set_target_properties(midispec PROPERTIES CXX_STANDARD 17)

if(MIDISPEC_BUILD_GTEST OR MIDISPEC_BUILD_VST3 OR MIDISPEC_BUILD_STANDALONE)
    set(RTMIDI_BUILD_TESTING OFF)
    add_subdirectory(external/rtmidi)
    target_link_libraries(midispec PUBLIC rtmidi)
endif()

if(MIDISPEC_BUILD_GTEST)
    set(BUILD_SHARED_LIBS OFF)
    add_subdirectory(external/gtest)
    target_link_libraries(midispec PUBLIC GTest::gtest_main)

    # midispec_test [Akai LPK25]
    add_executable(midispec_gtest_akai_lpk25 "test/gtest/gtest_akai_lpk25.cpp")
    set_target_properties(midispec_gtest_akai_lpk25 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_akai_lpk25 PRIVATE midispec)

    # midispec_test [Akai MPX8]
    add_executable(midispec_gtest_akai_mpx8 "test/gtest/gtest_akai_mpx8.cpp")
    set_target_properties(midispec_gtest_akai_mpx8 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_akai_mpx8 PRIVATE midispec)

    # midispec_test [Korg microKORG]
    add_executable(midispec_gtest_korg_microkorg "test/gtest/gtest_korg_microkorg.cpp")
    set_target_properties(midispec_gtest_korg_microkorg PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_korg_microkorg PRIVATE midispec)

    # midispec_test [Yamaha DX7]
    add_executable(midispec_gtest_yamaha_dx7 "test/gtest/gtest_yamaha_dx7.cpp")
    set_target_properties(midispec_gtest_yamaha_dx7 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_dx7 PRIVATE midispec)

    # midispec_test [Yamaha SPX90]
    add_executable(midispec_gtest_yamaha_spx90 "test/gtest/gtest_yamaha_spx90.cpp")
    set_target_properties(midispec_gtest_yamaha_spx90 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_spx90 PRIVATE midispec)

    # midispec_test [Yamaha TX81Z]
    add_executable(midispec_gtest_yamaha_tx81z "test/gtest/gtest_yamaha_tx81z.cpp")
    set_target_properties(midispec_gtest_yamaha_tx81z PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_gtest_yamaha_tx81z PRIVATE midispec)

endif()

if(MIDISPEC_BUILD_VST3 OR MIDISPEC_BUILD_STANDALONE)
    add_subdirectory(external/imgui)
    add_subdirectory(external/json)
    add_subdirectory(external/sdl)
    target_link_libraries(midispec PUBLIC imgui SDL2-static)
endif()

if(MIDISPEC_BUILD_VST3)
    

    # midispec_vst3 [Yamaha DX7]
    add_executable(midispec_vst3_yamaha_dx7 "test/vst3/vst3_yamaha_dx7.cpp")
    set_target_properties(midispec_vst3_yamaha_dx7 PROPERTIES CXX_STANDARD 17)
    target_link_libraries(midispec_vst3_yamaha_dx7 PRIVATE midispec)

endif()

if(MIDISPEC_BUILD_STANDALONE)


endif()