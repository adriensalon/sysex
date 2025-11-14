#pragma once

#include <vector>

#include <midispec/core/capabilities.hpp>
#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Yamaha SPX90 effect.
/// To reveive SysEx from the hardware internal wiring to MIDI THRU and MIDI OUT
/// must be switched by opening and modifying the hardware.
struct yamaha_spx90 {

    // channel common

    /// @brief Encodes a note off message.
    /// Only affects PITCH CHANGE and FREEZE B programs.
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    static void encode_note_off(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note);

    /// @brief Encodes a note on message.
    /// Only affects PITCH CHANGE and FREEZE B programs.
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    static void encode_note_on(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note);

    /// @brief Encodes a program change message.
    /// Logical programs are assigned to patch slots in the UTILITY menu
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param program MIDI program. In range [0, 127]
    static void encode_program_change(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> program);

    // system exclusive

    /// @brief Encodes a bank request message
    /// @param encoded Vector to decode the SysEx message from
    /// @param device Expected target device number. In range [0, 15]
    /// @param bank Selected bank to request. In range [0, 3]
    static void encode_program_patch_bank_request(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 3> bank);
};
}
