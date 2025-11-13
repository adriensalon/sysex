#pragma once

#include <iostream>

#include <midispec/test/gtest.hpp>

namespace midispec {

void test_gtest::send(std::vector<std::uint8_t>& encoded, const bool clear, const std::chrono::milliseconds debounce)
{
    _midi_out->sendMessage(&encoded);
    if (clear) {
        encoded.clear();
    }
    std::this_thread::sleep_for(debounce);
}

bool test_gtest::receive(std::vector<std::uint8_t>& encoded, const std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> _lock(_mutex);
    if (!_condition_variable.wait_for(_lock, timeout, [] { return _stop || !_queue.empty(); })) {
        return false;
    }

    const std::chrono::steady_clock::time_point _deadline = std::chrono::steady_clock::now() + timeout;
    while (!_stop) {
        if (!_queue.empty() && !_queue.front().empty() && _queue.front().front() == 0xF0) {
            encoded = std::move(_queue.front());
            _queue.pop_front();
            return true;
        }
        if (_queue.empty()) {
            const std::chrono::nanoseconds _left = _deadline - std::chrono::steady_clock::now();
            if (_left <= std::chrono::milliseconds(0)) {
                break;
            }
            _condition_variable.wait_for(_lock, _left, [] { return _stop || !_queue.empty(); });
            continue;
        }
        _queue.pop_front();
    }

    return false;
}

void test_gtest::SetUpTestSuite()
{
    _midi_in = std::make_unique<RtMidiIn>();
    _midi_out = std::make_unique<RtMidiOut>();

    const unsigned in_count = _midi_in->getPortCount();
    const unsigned out_count = _midi_out->getPortCount();
    if (0 >= in_count)
        throw std::runtime_error("Invalid input MIDI port");
    if (1 >= out_count)
        throw std::runtime_error("Invalid output MIDI port");

    std::cout << std::endl;
    std::cout << "Using input MIDI port " << _midi_in->getPortName(0) << "\n";
    std::cout << "Using output MIDI port " << _midi_out->getPortName(1) << "\n";
    std::cout << std::endl;

    _midi_in->openPort(0);
    _midi_in->ignoreTypes(false, true, true);
    _midi_in->setCallback(&test_gtest::midi_in_cb, nullptr);
    _midi_out->openPort(1);
}

void test_gtest::TearDownTestSuite()
{
    {
        std::lock_guard<std::mutex> _lock(_mutex);
        _stop = true;
    }
    _condition_variable.notify_all();
    _midi_in.reset();
    _midi_out.reset();
}

void test_gtest::SetUp()
{
    std::lock_guard<std::mutex> _lock(_mutex);
    _queue.clear();
    _stop = false;
}

void test_gtest::midi_in_cb(double, std::vector<std::uint8_t>* message, void*)
{
    std::lock_guard<std::mutex> _lock(_mutex);

    for (const std::uint8_t _byte : *message) {
        if (_byte == 0xF8 || _byte == 0xFA || _byte == 0xFB || _byte == 0xFC || _byte == 0xFE) {
            continue;
        }

        if (_accumulated.empty()) {
            if (_byte != 0xF0) {
                continue;
            }
            _accumulated.push_back(0xF0);
            continue;
        }

        _accumulated.push_back(_byte);

        if (_byte == 0xF7) {
            _queue.push_back(_accumulated);
            _accumulated.clear();
        }
    }

    _condition_variable.notify_one();
}

}
