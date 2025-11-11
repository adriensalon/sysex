#pragma once

#include <RtMidi.h>
#include <gtest/gtest.h>

#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>

#ifndef SYSEX_TEST_IN_MIDIPORT
#error "Define SYSEX_TEST_IN_MIDIPORT (input port index)"
#endif
#ifndef SYSEX_TEST_OUT_MIDIPORT
#error "Define SYSEX_TEST_OUT_MIDIPORT (output port index)"
#endif

namespace midispec {

/// @brief
struct hardware : public testing::Test {

    inline static std::chrono::milliseconds debounce_ms = std::chrono::milliseconds(50);

    static void SetUpTestSuite()
    {
        s_in = std::make_unique<RtMidiIn>();
        s_out = std::make_unique<RtMidiOut>();

        // Correct bounds check: index must be < count
        const unsigned in_count = s_in->getPortCount();
        const unsigned out_count = s_out->getPortCount();
        if (SYSEX_TEST_IN_MIDIPORT >= in_count)
            throw std::runtime_error("Invalid input MIDI port");
        if (SYSEX_TEST_OUT_MIDIPORT >= out_count)
            throw std::runtime_error("Invalid output MIDI port");

        std::cout << std::endl;
        std::cout << "Using input MIDI port " << s_in->getPortName(SYSEX_TEST_IN_MIDIPORT) << "\n";
        std::cout << "Using output MIDI port " << s_out->getPortName(SYSEX_TEST_OUT_MIDIPORT) << "\n";
        std::cout << std::endl;

        s_out->openPort(SYSEX_TEST_OUT_MIDIPORT);

        s_in->openPort(SYSEX_TEST_IN_MIDIPORT);
        // Receive SysEx, ignore timing & active sense
        s_in->ignoreTypes(/*sysex*/ false, /*timing*/ true, /*sensing*/ true);
        s_in->setCallback(&hardware::midi_in_cb, nullptr);
    }

    static void TearDownTestSuite()
    {
        {
            std::lock_guard<std::mutex> lk(s_mu);
            s_stop = true;
        }
        s_cv.notify_all();
        s_in.reset();
        s_out.reset();
    }

    void SetUp() override
    {
        std::lock_guard<std::mutex> lk(s_mu);
        s_queue.clear();
        s_stop = false;
    }

protected:
    static void send(std::vector<std::uint8_t>& bytes)
    {
        std::vector<unsigned char> msg(bytes.begin(), bytes.end());
        s_out->sendMessage(&msg);
        bytes.clear();
        std::this_thread::sleep_for(debounce_ms);
    }

    static bool receive(std::vector<unsigned char>& out, int timeout_ms = 5000)
    {
        std::unique_lock<std::mutex> lk(s_mu);
        auto ready = [] {
            return !s_queue.empty() && !s_queue.front().empty() && s_queue.front().front() == 0xF0;
        };
        if (!s_cv.wait_for(lk, std::chrono::milliseconds(timeout_ms), [] { return s_stop || !s_queue.empty(); }))
            return false;
        // Drain non-SysEx if any, keep waiting within timeout
        auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
        while (!s_stop) {
            if (ready()) {
                out = std::move(s_queue.front());
                s_queue.pop_front();
                return true;
            }
            if (s_queue.empty()) {
                auto left = deadline - std::chrono::steady_clock::now();
                if (left <= std::chrono::milliseconds(0))
                    break;
                s_cv.wait_for(lk, left, [] { return s_stop || !s_queue.empty(); });
                continue;
            }
            // Drop non-SysEx noise
            s_queue.pop_front();
        }
        return false;
    }

private:
    static inline std::vector<unsigned char> s_acc; // accumulates current SysEx

    static inline bool isRealtime(unsigned char b)
    {
        return b == 0xF8 || b == 0xFA || b == 0xFB || b == 0xFC || b == 0xFE;
    }

    static void midi_in_cb(double /*ts*/, std::vector<unsigned char>* msg, void* /*user*/)
    {
        std::lock_guard<std::mutex> lk(s_mu);

        for (auto b : *msg) {
            if (isRealtime(b))
                continue; // drop RT noise

            if (s_acc.empty()) {
                if (b != 0xF0)
                    continue; // wait for start
                s_acc.push_back(0xF0);
                continue;
            }

            s_acc.push_back(b);
            if (b == 0xF7) { // complete frame
                s_queue.push_back(s_acc); // enqueue ONE clean F0..F7
                s_acc.clear();
            }
        }
        s_cv.notify_one();
    }

    inline static std::unique_ptr<RtMidiIn> s_in;
    inline static std::unique_ptr<RtMidiOut> s_out;
    inline static std::mutex s_mu;
    inline static std::condition_variable s_cv;
    inline static std::deque<std::vector<unsigned char>> s_queue;
    inline static bool s_stop;
};

}
