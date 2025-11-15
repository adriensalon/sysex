#pragma once

#include <array>
#include <vector>

#include <midispec/core/capabilities.hpp>
#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Akai LPK25 controller.
/// Undocumented SysEx interface for TX and RX preset bulk data.
/// Sniff packets from the editor to reverse
struct akai_lpk25 {

    // channel common

    /// @brief Encodes a note off message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    static void encode_note_off(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note);

    /// @brief Decodes a note off message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @return true on success
    static bool decode_note_off(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 127>& note);

    /// @brief Encodes a note on message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    static void encode_note_on(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note);

    /// @brief Decodes a note on message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    /// @return true on success
    static bool decode_note_on(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 127>& note,
        integral<std::uint8_t, 0, 127>& velocity);

    // system common

    /// @brief Encodes a clock message
    /// @param encoded Vector to append the encoded message to
    static void encode_clock(std::vector<std::uint8_t>& encoded);

    /// @brief Encodes a song position pointer message
    /// @param encoded Vector to append the encoded message to
    /// @param data MIDI song position pointer. In range [0, 16383]
    static void encode_song_position(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint16_t, 0, 16383> data);

    /// @brief Encodes a continue message
    /// @param encoded Vector to append the encoded message to
    static void encode_continue(std::vector<std::uint8_t>& encoded);

    /// @brief Decodes a reset message
    /// @param encoded Vector to read the encoded message from
    /// @return true on success (message is a system reset)
    static bool decode_reset(const std::vector<std::uint8_t>& encoded);
};
}
