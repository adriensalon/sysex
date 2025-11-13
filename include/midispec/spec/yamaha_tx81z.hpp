#pragma once

#include <array>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief 
namespace yamaha_tx81z {

    struct voice_patch {
        std::array<char, 10> voice_name;
        std::array<integral<std::uint8_t, 0, 31>, 4> op_attack_rate;
        std::array<integral<std::uint8_t, 0, 31>, 4> op_decay_rate_1;
        std::array<integral<std::uint8_t, 0, 31>, 4> op_decay_rate_2;
        std::array<integral<std::uint8_t, 0, 14>, 4> op_release_rate;
        std::array<integral<std::uint8_t, 0, 15>, 4> op_decay_level_1;
        std::array<integral<std::uint8_t, 0, 99>, 4> op_level_scaling;
        std::array<integral<std::uint8_t, 0, 3>, 4> op_rate_scaling;
        std::array<integral<std::uint8_t, 0, 7>, 4> op_envelope_generator_bias_sensitivity;
        std::array<integral<std::uint8_t, 0, 1>, 4> op_amplitude_modulation_enable;
        std::array<integral<std::uint8_t, 0, 7>, 4> op_key_velocity_sensitivity;
        std::array<integral<std::uint8_t, 0, 99>, 4> op_output_level;
        std::array<integral<std::uint8_t, 0, 63>, 4> op_frequency;
        std::array<integral<std::uint8_t, 0, 6, 3>, 4> op_detune;
        std::array<integral<std::uint8_t, 0, 1>, 4> op_fixed_frequency;
        std::array<integral<std::uint8_t, 0, 7>, 4> op_fixed_frequency_range;
        std::array<integral<std::uint8_t, 0, 15>, 4> op_frequency_range_fine;
        std::array<integral<std::uint8_t, 0, 7>, 4> op_waveform;
        std::array<integral<std::uint8_t, 0, 3>, 4> op_envelope_generator_shift;
        integral<std::uint8_t, 0, 7> algorithm_mode;
        integral<std::uint8_t, 0, 7> algorithm_feedback;
        integral<std::uint8_t, 0, 99> lfo_speed;
        integral<std::uint8_t, 0, 99> lfo_delay;
        integral<std::uint8_t, 0, 99> pitch_modulation_depth;
        integral<std::uint8_t, 0, 99> amplitude_modulation_depth;
        integral<std::uint8_t, 0, 1> lfo_sync;
        integral<std::uint8_t, 0, 3> lfo_wave;
        integral<std::uint8_t, 0, 7> pitch_modulation_sensitivity;
        integral<std::uint8_t, 0, 3> amplitude_modulation_sensitivity;
        integral<std::uint8_t, 0, 48, 24> transpose;
        integral<std::uint8_t, 0, 1> poly_mono;
        integral<std::uint8_t, 0, 12> pitchbend_range;
        integral<std::uint8_t, 0, 1> portamento_mode;
        integral<std::uint8_t, 0, 99> portamento_time;
        integral<std::uint8_t, 0, 99> foot_controller_volume;
        integral<std::uint8_t, 0, 1> sustain;
        integral<std::uint8_t, 0, 1> portamento;
        integral<std::uint8_t, 0, 1> chorus;
        integral<std::uint8_t, 0, 99> modulation_wheel_pitch;
        integral<std::uint8_t, 0, 99> modulation_wheel_amplitude;
        integral<std::uint8_t, 0, 99> breath_controller_pitch;
        integral<std::uint8_t, 0, 99> breath_controller_amplitude;
        integral<std::uint8_t, 0, 99, 50> breath_controller_pitch_bias;
        integral<std::uint8_t, 0, 99> breath_controller_envelope_generator_bias;
        integral<std::uint8_t, 0, 15> op_enable_mask;
        integral<std::uint8_t, 0, 7> reverb_rate;
        integral<std::uint8_t, 0, 99> foot_controller_pitch;
        integral<std::uint8_t, 0, 99> foot_controller_amplitude;
    };

    struct performance_patch {
        std::array<char, 10> performance_name;
        std::array<integral<std::uint8_t, 0, 8>, 8> inst_maximum_notes;
        std::array<integral<std::uint8_t, 0, 159>, 8> inst_voice_number;
        std::array<integral<std::uint8_t, 0, 16>, 8> inst_receive_channel;
        std::array<integral<std::uint8_t, 0, 127>, 8> inst_low_note_limit;
        std::array<integral<std::uint8_t, 0, 127>, 8> inst_high_note_limit;
        std::array<integral<std::uint8_t, 0, 14, 7>, 8> inst_detune;
        std::array<integral<std::uint8_t, 0, 48, 24>, 8> inst_note_shift;
        std::array<integral<std::uint8_t, 0, 99>, 8> inst_volume;
        std::array<integral<std::uint8_t, 0, 3>, 8> inst_output_assign;
        std::array<integral<std::uint8_t, 0, 3>, 8> inst_lfo_select;
        std::array<integral<std::uint8_t, 0, 1>, 8> inst_microtune_enable;
        integral<std::uint8_t, 0, 12> microtune_table;
        integral<std::uint8_t, 0, 1> assign_mode;
        integral<std::uint8_t, 0, 3> effect_select;
        integral<std::uint8_t, 0, 1> microtune_key;
    };

    struct system_patch {
        std::array<char, 16> system_id;
        integral<std::uint8_t, 0, 127, 64> master_tune;
        integral<std::uint8_t, 0, 16> basic_receive_channel;
        integral<std::uint8_t, 0, 15> transmit_channel;
        integral<std::uint8_t, 0, 2> program_change_switch;
        integral<std::uint8_t, 0, 17> controller_change_switch;
        integral<std::uint8_t, 0, 17> pitchbend_switch;
        integral<std::uint8_t, 0, 2> note_on_off;
        integral<std::uint8_t, 0, 1> exclusive_on_off;
        integral<std::uint8_t, 0, 1> memory_protect;
        integral<std::uint8_t, 0, 1> combine;
        integral<std::uint8_t, 0, 1> after_touch;
    };

    struct effect_patch {
        integral<std::uint8_t, 0, 127> effect_time_1;
        integral<std::uint8_t, 0, 48, 24> effect_pitch_1;
        integral<std::uint8_t, 0, 7> effect_feedback_1;
        integral<std::uint8_t, 0, 99> effect_level_1;
        integral<std::uint8_t, 0, 1> effect_direction_2;
        integral<std::uint8_t, 0, 3> effect_select_2;
        integral<std::uint8_t, 0, 99> effect_range_2;
        integral<std::uint8_t, 0, 49, 25> effect_chord_note_3;
        std::array<integral<std::uint8_t, 0, 1>, 12> effect_key_3;
    };

    struct microtune_patch {
    };

    namespace channel_common {

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

        /// @brief Encodes a note on message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @param aftertouch MIDI velocity. In range [0, 127]
        void encode_note_aftertouch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note,
            const integral<std::uint8_t, 0, 127> aftertouch);

        /// @brief Encodes a program change message.
        /// Logical programs are assigned to patch slots by the hardware
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param program MIDI program. In range [0, 127]
        void encode_program_change(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> program);

        /// @brief Encodes a pitch bend change message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param pitchbend MIDI pitch bend. In range [0, 16383] (Default 8192)
        void encode_pitchbend(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint16_t, 0, 16383, 8192> pitchbend);
    }

    namespace channel_cc {

        /// @brief CC1
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_modulation_wheel(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC2
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_breath_controller(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC4
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_foot_controller(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC5
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_portamento_time(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC7
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_volume(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC10
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_pan(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC64
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_sustain(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief CC65
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_portamento(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);
    }

    namespace system_common {

        /// @brief
        /// @param encoded
        void encode_all_notes_off(std::vector<std::uint8_t>& encoded);

        /// @brief
        /// @param encoded
        void encode_active_sens(std::vector<std::uint8_t>& encoded);
    }

    namespace system_exclusive {

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
            const voice_patch& data);

        void encode_bank(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const std::array<voice_patch, 128>& data);

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
            const system_patch& data);

        void encode_program_change_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device,
            const std::array<integral<std::uint8_t, 0, 127>, 127>& data);

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

        void encode_program_change_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        void encode_microtune_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15>& device);

        //

        void decode_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            voice_patch& data);

        void decode_bank(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            std::array<voice_patch, 128>& data);

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
}
}
