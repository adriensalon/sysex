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
            
        // after touch (requires CC switch on)
            
        // pitch bend (requires PB switch on)

        // CC (requires CC switch on)
        // CC 1 : modulation wheel
        // CC 2 : breath controller
        // CC 4 : foot controller
        // CC 5 : portamento time (single mode only)
        // CC 7 : volume
        // CC 10 : pan (performance mode only)
        // CC 64 : sustain
        // CC 65 : portamento

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
            std::array<integral<std::uint8_t, 0, 63>, 4> op_frequency_coarse;
            std::array<integral<std::uint8_t, 0, 15>, 4> op_frequency_fine;
            std::array<integral<std::uint8_t, 0, 7>, 4> op_fixed_frequency_range;
            std::array<integral<std::uint8_t, 0, 7>, 4> op_waveform;
            std::array<integral<std::uint8_t, 0, 14>, 4> op_detune;
            std::array<integral<std::uint8_t, 0, 31>, 4> op_attack_rate;
            std::array<integral<std::uint8_t, 0, 31>, 4> op_decay_rate_1;
            std::array<integral<std::uint8_t, 0, 31>, 4> op_decay_rate_2;
            std::array<integral<std::uint8_t, 0, 15>, 4> op_release_rate;
            std::array<integral<std::uint8_t, 0, 15>, 4> op_decay_level_1;
            std::array<bool, 4> op_amplitude_modulation;
            std::array<integral<std::uint8_t, 0, 7>, 4> op_envelope_generator_scaling;
            std::array<integral<std::uint8_t, 0, 7>, 4> op_envelope_generator_bias_sensitivity;
            std::array<integral<std::uint8_t, 0, 3>, 4> op_envelope_generator_shift;

            integral<std::uint8_t, 0, 7> algorithm_mode;
            integral<std::uint8_t, 0, 7> algorithm_feedback;
            integral<std::uint8_t, 0, 99> lfo_speed;
            integral<std::uint8_t, 0, 99> lfo_delay;
            integral<std::uint8_t, 0, 99> lfo_pitch_modulation_depth;
            integral<std::uint8_t, 0, 99> lfo_amplitude_modulation_depth;
            bool lfo_sync;
            integral<std::uint8_t, 0, 3> lfo_wave;
            integral<std::uint8_t, 0, 7> pitch_modulation_sensitivity;
            integral<std::uint8_t, 0, 7> amplitude_modulation_sensitivity;
            integral<std::uint8_t, 0, 7> transpose_cents;
            bool mono_poly;
            integral<std::uint8_t, 0, 12> pitch_bend_range;
            bool portamento_mode;
            integral<std::uint8_t, 0, 99> portamento_time;
            integral<std::uint8_t, 0, 99> portamento_volume;
        };

        struct performance_patch {
        };

        struct system_patch {
        };

        struct effect_patch {
        };

        struct microtune_patch {
        };

        void encode_op_rate_scaling_depth(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const integral<std::uint8_t, 0, 3>& op,
            const integral<std::uint8_t, 0, 3>& data);

        void encode_op_key_velocity_sensitivity(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const integral<std::uint8_t, 0, 3>& op,
            const integral<std::uint8_t, 0, 7>& data);

        // etc...

        // buttons comme le dx7

        void encode_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const patch& data);

        void encode_bank(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const std::array<patch, 128>& data);

        void encode_performance_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const performance_patch& data);

        void encode_system_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const system_patch& data);

        void encode_effect_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const effect_patch& data);

        void encode_microtune_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const microtune_patch& data);

        //

        void encode_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_bank_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_performance_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_system_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_effect_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_microtune_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        //

        void decode_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            patch& data);

        void decode_bank(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            std::array<patch, 128>& data);

        void decode_performance_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            performance_patch& data);

        void decode_system_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            system_patch& data);

        void decode_effect_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            effect_patch& data);

        void decode_microtune_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            microtune_patch& data);
    }

    namespace system_realtime {

        void encode_all_notes_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel);

        void encode_active_sens(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel);

    }
}
}
