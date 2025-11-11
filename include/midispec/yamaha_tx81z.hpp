#pragma once

#include <array>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {

namespace yamaha_tx81z {

    namespace channel_voice {

        /// @brief Encodes a note off message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        void encode_note_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note);

        /// @brief Encodes a note on message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @param velocity MIDI velocity. In range [0, 127]
        void encode_note_on(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note,
            const integral<std::uint8_t, 0, 127> velocity);

        /// @brief Encodes a program change message.
        /// Logical programs are assigned to patch slots by the hardware
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param program MIDI program. In range [0, 127]
        void encode_program_change(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> program);
    }

    namespace system_exclusive {

        /// @brief Operator oscillator frequency mode.
        /// Selects between ratio (pitch follows key) and fixed (absolute frequency) behavior.
        /// In range [0, 1]
        enum struct oscillator_mode : std::uint8_t {
            /// @brief Ratio mode: frequency = key pitch × coarse/fine ratio; tracks keyboard pitch
            ratio = 0,
            /// @brief Fixed mode: frequency is absolute; coarse/fine select a fixed Hz value (not key-tracking)
            fixed = 1
        };

        struct patch {
            std::array<integral<std::uint8_t, 0, 3>, 4> op_rate_scaling_depth;
            std::array<integral<std::uint8_t, 0, 7>, 4> op_key_velocity_sensitivity;
            std::array<integral<std::uint8_t, 0, 99>, 4> op_output_level;
            std::array<oscillator_mode, 4> op_oscillator_mode;
            std::array<integral<std::uint8_t, 0, 15>, 4> op_frequency_multiple;
            std::array<integral<std::uint8_t, 0, 15>, 4> op_frequency_fine;
            std::array<integral<std::uint8_t, 0, 14>, 4> op_detune;
            std::array<integral<std::uint8_t, 0, 31>, 4> op_attack_rate;
        };
    }
}
}
