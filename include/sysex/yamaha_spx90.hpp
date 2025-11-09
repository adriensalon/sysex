#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <sysex/core/parameter.hpp>

namespace sysex {

/// @brief 
namespace yamaha_spx90 {

    /// @brief Devices correspond to hardware units.
    /// Each hardware unit represent a device that can be selected directly on the hardware.
    /// Some hardware can be configured to receive messages from all devices.
    /// Devices can be used to link multiple hardware to a single MIDI input or output.
    /// Range is [0, 15]
    using device_id = std::uint8_t;

    enum struct effect_type : std::uint8_t {
        hall_reverb = 0,
        room_reverb,
        plate_reverb,
        reverse_reverb,
        gated_reverb,
        early_reflections,
        delay, // single / echo
        chorus,
        flanger,
        phaser,
        tremolo,
        pan,
        pitch_change,
        compressor,
        noise_gate,
        freeze,
        unknown = 0x7F
    };

    struct parameter {
        std::uint8_t program_number = 31; // target program
        std::uint8_t param_index = 0; // which parameter within that program
        std::uint8_t value = 0; // 0..127
    };

    // A single “program” in SPX90 (preset or user).
    // Each program has a small set of 7-bit params (count varies per effect).
    // We expose a generic param array; leave unused tail as 0.
    struct program {
        std::uint8_t number = 1; // 1..90 (1..30 ROM, 31..90 user)
        effect_type type = effect_type::unknown;
        std::array<std::uint8_t, 16> param {}; // 0..127 (SPX90 params are 7-bit)
        std::array<char, 8> name {}; // ASCII, padded with spaces
    };

    // Full user bank (typically 60 user programs: 31..90).
    // We store 90 slots for convenience; ROM entries can be ignored or treated read-only.
    struct bank {
        std::array<program, 90> programs {};
    };

    // Minimal system settings the SPX90 exposes over MIDI (kept generic).
    struct system_block {
        bool prog_change_enable = true; // respond to Program Change
        bool sys_info_avail = true; // bulk enable
    };

}   

// encode

void encode(std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, const yamaha_spx90::parameter& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, const yamaha_spx90::program& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, const yamaha_spx90::bank& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, const yamaha_spx90::system_block& data);

// decode

void decode(const std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, yamaha_spx90::program& data);
void decode(const std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, yamaha_spx90::bank& data);
void decode(const std::vector<std::uint8_t>& encoded, const yamaha_spx90::device_id device, yamaha_spx90::system_block& data);

}
