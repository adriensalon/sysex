#pragma once

#include <array>
#include <vector>

#include <midispec/core/capabilities.hpp>
#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Akai MPX8 controller
struct akai_mpx8 {

    // channel common

    /// @brief Encodes a note off message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    static void encode_note_off(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note,
        const integral<std::uint8_t, 0, 127> velocity);

    /// @brief Decodes a note off message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    /// @return true on success
    static bool decode_note_off(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 127>& note,
        integral<std::uint8_t, 0, 127>& velocity);

    /// @brief Encodes a note on message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    static void encode_note_on(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 127> note,
        const integral<std::uint8_t, 0, 127> velocity);

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

    /// @brief Decodes a note aftertouch message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param note MIDI note. In range [0, 127]
    /// @param after_touch MIDI aftertouch. In range [0, 127]
    /// @return true on success
    static bool decode_note_aftertouch(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 127>& note,
        integral<std::uint8_t, 0, 127>& aftertouch);

    // system exclusive

    /// @brief Encodes a universal inquiry request message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 127]
    static void encode_universal_inquiry_request(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 127> device);

    /// @brief Decodes a universal inquiry request message
    /// @param encoded Vector to read the encoded message from
    /// @param device Target device number. In range [0, 127]
    /// @param manufacturer MIDI hardware manufacturer info
    /// @param family MIDI hardware family info
    /// @param model MIDI hardware model info
    /// @param version MIDI hardware version info
    /// @return true on success
    static bool decode_universal_inquiry(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 127>& device,
        std::uint32_t& manufacturer,
        std::uint32_t& family,
        std::uint32_t& model,
        std::uint32_t& version);
};
}
