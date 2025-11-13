#pragma once

#include <gtest/gtest.h>
#include <RtMidi.h>

#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>

namespace midispec {

/// @brief
struct test_gtest : public testing::Test {

    /// @brief 
    /// @param encoded 
    /// @param clear 
    /// @param debounce 
    static void send(
        std::vector<std::uint8_t>& encoded, 
        const bool clear = true, 
        const std::chrono::milliseconds debounce = std::chrono::milliseconds(50));

    /// @brief 
    /// @param encoded 
    /// @param timeout 
    /// @return true on success
    static bool receive(
        std::vector<std::uint8_t>& encoded, 
        const std::chrono::milliseconds timeout = std::chrono::milliseconds(5000));

protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;

private:
    inline static std::vector<std::uint8_t> _accumulated;
    inline static std::unique_ptr<RtMidiIn> _midi_in;
    inline static std::unique_ptr<RtMidiOut> _midi_out;
    inline static std::mutex _mutex;
    inline static std::condition_variable _condition_variable;
    inline static std::deque<std::vector<std::uint8_t>> _queue;
    inline static bool _stop;

    static void midi_in_cb(double, std::vector<std::uint8_t>* message, void*);
};

}
