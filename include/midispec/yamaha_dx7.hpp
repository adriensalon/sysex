#pragma once

#include <array>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Yamaha DX7 synthesizer.
/// To allow SysEx, edit FUNCTION > 8 to show SYS INFO AVAIL.
/// It can receive SysEx for a patch or a 32 patches bank (entire internal memory).
/// It can only send the current 32 patches bank by editing FUNCTION > 8 to show MIDI TRANSMIT?.
/// A workaround by sending these commands from SysEx is demonstrated in the 'test/test_yamaha_dx7.cpp' file.
namespace yamaha_dx7 {

    namespace channel_voice {

        /// @brief Encodes a note off message.
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        void encode_note_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note);

        /// @brief Encodes a note on message.
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
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param program MIDI program clamped for the DX7. In range [0, 31]
        void encode_program_change(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 31> program);

        /// @brief Encodes a pitch bend change message.
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param pitch_bend MIDI pitch bend. In range [0, 16383] (Default 8192)
        void encode_pitch_bend_change(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint16_t, 0, 16383, 8192> pitch_bend);

        /// @brief Decodes a note off message.
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @return true on success
        bool decode_note_off(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note);

        /// @brief Decodes a note on message.
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @param velocity MIDI velocity. In range [0, 127]
        /// @return true on success
        bool decode_note_on(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note,
            integral<std::uint8_t, 0, 127>& velocity);

        /// @brief Decodes a program change message.
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param program MIDI program clamped for the DX7. In range [0, 31]
        /// @return true on success
        bool decode_program_change(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 31>& program);

        /// @brief Decodes a channel pressure (mono after touch) message.
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param program Nonstandard MIDI channel pressure. In range [0, 127]
        /// @return true on success
        bool decode_channel_pressure(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& pressure);

        /// @brief Decodes a pitch bend change message.
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param pitch_bend MIDI pitch bend. In range [0, 16383] (Default 8192)
        /// @return true on success
        bool decode_pitch_bend_change(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint16_t, 0, 16383, 8192>& pitch_bend);
    }

    namespace system_exclusive {

        /// @brief Keyboard level-scaling curve used by each operator.
        /// Controls how output level changes left/right of the breakpoint.
        /// See per-value polarity and taper behavior.
        /// In range [0, 3]
        enum struct keyboard_scaling_curve : std::uint8_t {
            /// @brief Negative linear: level decreases linearly as you move away from the breakpoint
            negative_linear = 0,
            /// @brief Positive linear: level increases linearly as you move away from the breakpoint
            positive_linear = 1,
            /// @brief Negative exponential: level decreases exponentially (steeper near breakpoint)
            negative_exponential = 2,
            /// @brief Positive exponential: level increases exponentially (steeper near breakpoint)
            positive_exponential = 3
        };

        /// @brief Operator oscillator frequency mode.
        /// Selects between ratio (pitch follows key) and fixed (absolute frequency) behavior.
        /// In range [0, 1]
        enum struct oscillator_mode : std::uint8_t {
            /// @brief Ratio mode: frequency = key pitch × coarse/fine ratio; tracks keyboard pitch
            ratio = 0,
            /// @brief Fixed mode: frequency is absolute; coarse/fine select a fixed Hz value (not key-tracking)
            fixed = 1
        };

        /// @brief Global LFO waveform selection.
        /// Affects pitch (PM) and amplitude (AM) modulation destinations.
        /// In range [0, 4]
        enum struct waveform_mode : std::uint8_t {
            /// @brief Triangle
            triangle = 0,
            /// @brief Saw down
            saw_down = 1,
            /// @brief Saw up
            saw_up = 2,
            /// @brief Square
            square = 3,
            /// @brief Sine
            sine = 4
        };

        /// @brief Global mono/poly mode.
        /// In range [0, 1]
        enum struct mono_poly_mode : std::uint8_t {
            monophonic = 0,
            polyphonic = 1,
        };

        /// @brief Global portamento mode.
        /// In range [0, 1]
        enum struct portamento_mode : std::uint8_t {
            /// @brief Remembers old pitch and always glides
            retain = 0,
            /// @brief Follows keypress behavior (only glides if overlapping)
            follow = 1,
        };

        /// @brief Yamaha DX7 voice (patch) parameters.
        /// Represents one complete 155 byte DX7 voice as used in SysEx single-voice dumps.
        /// Includes all six operators, pitch envelope, algorithm, LFO, and global voice settings
        struct patch {
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_rate_1;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_rate_2;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_rate_3;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_rate_4;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_level_1;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_level_2;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_level_3;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_envelope_generator_level_4;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_breakpoint;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_left_depth;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_right_depth;
            std::array<keyboard_scaling_curve, 6> op_keyboard_scaling_left_curve;
            std::array<keyboard_scaling_curve, 6> op_keyboard_scaling_right_curve;
            std::array<integral<std::uint8_t, 0, 7>, 6> op_keyboard_scaling_rate;
            std::array<integral<std::uint8_t, 0, 3>, 6> op_amplitude_modulation_sensitivity;
            std::array<integral<std::uint8_t, 0, 7>, 6> op_velocity_sensitivity;
            std::array<integral<std::uint8_t, 0, 99, 99>, 6> op_output_level;
            std::array<oscillator_mode, 6> op_oscillator_mode;
            std::array<integral<std::uint8_t, 0, 31>, 6> op_oscillator_coarse;
            std::array<integral<std::uint8_t, 0, 99>, 6> op_oscillator_fine;
            std::array<integral<std::uint8_t, 0, 14, 7>, 6> op_oscillator_detune;
            integral<std::uint8_t, 0, 99> pitch_envelope_rate_1;
            integral<std::uint8_t, 0, 99> pitch_envelope_rate_2;
            integral<std::uint8_t, 0, 99> pitch_envelope_rate_3;
            integral<std::uint8_t, 0, 99> pitch_envelope_rate_4;
            integral<std::uint8_t, 0, 99> pitch_envelope_level_1;
            integral<std::uint8_t, 0, 99> pitch_envelope_level_2;
            integral<std::uint8_t, 0, 99> pitch_envelope_level_3;
            integral<std::uint8_t, 0, 99> pitch_envelope_level_4;
            integral<std::uint8_t, 0, 31> algorithm_mode;
            integral<std::uint8_t, 0, 7> algorithm_feedback;
            bool oscillator_key_sync;
            waveform_mode lfo_waveform_mode;
            integral<std::uint8_t, 0, 99> lfo_speed;
            integral<std::uint8_t, 0, 99> lfo_delay;
            integral<std::uint8_t, 0, 99> lfo_pitch_modulation_depth;
            integral<std::uint8_t, 0, 99> lfo_amplitude_modulation_depth;
            bool lfo_sync;
            integral<std::uint8_t, 0, 7> pitch_modulation_sensitivity;
            integral<std::uint8_t, 0, 48, 24> transpose_semitones;
            std::array<char, 10> patch_name;
        };

        /// @brief Encodes an operator envelope generator rate 1 (attack rate) parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator rate 1. In range [0, 99]
        void encode_op_envelope_generator_rate_1(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator rate 2 (decay 1 rate) parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator rate 1. In range [0, 99]
        void encode_op_envelope_generator_rate_2(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator rate 3 (decay 2 rate) parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator rate 1. In range [0, 99]
        void encode_op_envelope_generator_rate_3(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator rate 4 (release rate) parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator rate 4. In range [0, 99]
        void encode_op_envelope_generator_rate_4(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator level 1 parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator level 1. In range [0, 99]
        void encode_op_envelope_generator_level_1(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator level 2 parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator level 2. In range [0, 99]
        void encode_op_envelope_generator_level_2(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator level 3 parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator level 3. In range [0, 99]
        void encode_op_envelope_generator_level_3(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator envelope generator level 4 parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Envelope generator level 3. In range [0, 99]
        void encode_op_envelope_generator_level_4(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator keyboard scaling breakpoint parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Breakpoint key. In range [0, 99]
        void encode_op_keyboard_scaling_breakpoint(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator keyboard scaling left depth parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Left depth. In range [0, 99]
        void encode_op_keyboard_scaling_left_depth(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator keyboard scaling right depth parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Right depth. In range [0, 99]
        void encode_op_keyboard_scaling_right_depth(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator keyboard scaling left curve parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Left curve (see op_keyboard_scaling_curve)
        void encode_op_keyboard_scaling_left_curve(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const keyboard_scaling_curve data);

        /// @brief Encodes an operator keyboard scaling right curve parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Right curve (see op_keyboard_scaling_curve)
        void encode_op_keyboard_scaling_right_curve(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const keyboard_scaling_curve data);

        /// @brief Encodes an operator keyboard scaling rate (key rate scaling) parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Rate scaling. In range [0, 7]
        void encode_op_keyboard_scaling_rate(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes an operator amplitude modulation sensitivity parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data AM sensitivity. In range [0, 3]
        void encode_op_amplitude_modulation_sensitivity(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 3> data);

        /// @brief Encodes an operator velocity sensitivity parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Velocity sensitivity. In range [0, 7]
        void encode_op_velocity_sensitivity(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes an operator output level parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Output level. In range [0, 99] (default 99)
        void encode_op_output_level(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99, 99> data);

        /// @brief Encodes an operator oscillator mode parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Oscillator mode (ratio or fixed)
        void encode_op_oscillator_mode(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const oscillator_mode data);

        /// @brief Encodes an operator oscillator coarse parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Coarse frequency. In range [0, 31]
        void encode_op_oscillator_coarse(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 31> data);

        /// @brief Encodes an operator oscillator fine parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Fine frequency. In range [0, 99]
        void encode_op_oscillator_fine(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes an operator oscillator detune parameter change message.
        /// This parameter applies to the current patch for the selected operator
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Detune amount. In range [0, 14] with center at 7
        void encode_op_oscillator_detune(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 5> op,
            const integral<std::uint8_t, 0, 14, 7> data);

        /// @brief Encodes pitch envelope generator rate 1 (attack) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG rate 1. In range [0, 99]
        void encode_pitch_envelope_rate_1(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator rate 2 (decay 1) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG rate 2. In range [0, 99]
        void encode_pitch_envelope_rate_2(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator rate 3 (decay 2) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG rate 3. In range [0, 99]
        void encode_pitch_envelope_rate_3(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator rate 4 (release) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG rate 4. In range [0, 99]
        void encode_pitch_envelope_rate_4(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator level 1 parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param op Operator index. In range [0, 5]
        /// @param data Pitch EG level 1. In range [0, 99]
        void encode_pitch_envelope_level_1(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator level 2 parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG level 2. In range [0, 99]
        void encode_pitch_envelope_level_2(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator level 3 parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG level 2. In range [0, 99]
        void encode_pitch_envelope_level_3(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes pitch envelope generator level 4 parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Pitch EG level 2. In range [0, 99]
        void encode_pitch_envelope_level_4(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes algorithm (operator routing) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Algorithm number. In range [0, 31]
        void encode_algorithm_mode(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 31> data);

        /// @brief Encodes algorithm feedback amount parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Feedback. In range [0, 7]
        void encode_algorithm_feedback(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes oscillator key sync enable/disable parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true to enable, false to disable
        void encode_oscillator_key_sync(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes LFO waveform parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data LFO waveform (see lfo_waveform_mode)
        void encode_lfo_waveform(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const waveform_mode data);

        /// @brief Encodes LFO speed parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data LFO speed. In range [0, 99]
        void encode_lfo_speed(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes LFO delay parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data LFO delay. In range [0, 99]
        void encode_lfo_delay(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes LFO pitch modulation depth parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data PMD (pitch modulation depth). In range [0, 99]
        void encode_lfo_pitch_modulation_depth(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes LFO amplitude modulation depth parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data AMD (amplitude modulation depth). In range [0, 99]
        void encode_lfo_amplitude_modulation_depth(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes LFO sync on key-on enable/disable parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true to enable, false to disable
        void encode_lfo_sync(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes pitch modulation sensitivity (global) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data PMS (pitch modulation sensitivity). In range [0, 7]
        void encode_pitch_modulation_sensitivity(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes transpose (coarse tune in semitones) parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Transpose semitones. In range [-24, 24] (0 = concert)
        void encode_transpose_semitones(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 48, 24> data);

        /// @brief Encodes operator enable mask parameter change message.
        /// Each bit enables/disables one operator (OP1..OP6).
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Bitmask for operators. In range [0x00, 0x3F] (Default 0x3F = all on)
        void encode_op_enable_mask(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0x00, 0x3F, 0x3F> data);

        /// @brief Encodes patch name parameter change message.
        /// This parameter applies to the current patch
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data 10-character patch name (ASCII)
        void encode_patch_name(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const std::array<char, 10>& data);

        /// @brief Encodes mono mode enable/disable parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data false for mono, false for poly
        void encode_mono_poly_mode(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const mono_poly_mode data);

        /// @brief Encodes pitch bend range (semitones) parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Upward bend range. In range [0, 12] (Default 2)
        void encode_pitch_bend_range_semitones(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 12, 2> data);

        /// @brief Encodes pitch bend step parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Downward bend step. In range [0, 12]
        void encode_pitch_bend_step(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 12> data);

        /// @brief Encodes portamento mode parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Portamento mode. In range [0, 1]
        void encode_portamento_mode(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const portamento_mode data);

        /// @brief Encodes portamento glissando mode enable/disable parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true to enable, false to disable
        void encode_portamento_glissando(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes portamento time parameter change message.
        /// This parameter applies to the current patch (performance behavior)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Portamento time. In range [0, 99]
        void encode_portamento_time(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes modulation wheel range parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Modulation wheel range. In range [0, 99]
        void encode_modulation_wheel_range(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes modulation wheel assign parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Modulation wheel assign. In range [0, 7]
        void encode_modulation_wheel_assign(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes foot controller range parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Foot controller range. In range [0, 99]
        void encode_foot_controller_range(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes foot controller assign parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Foot controller assign. In range [0, 7]
        void encode_foot_controller_assign(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes breath controller range parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Breath controller range. In range [0, 99]
        void encode_breath_controller_range(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes breath controller assign parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Breath controller assign. In range [0, 7]
        void encode_breath_controller_assign(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes after touch range parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data After touch controller range. In range [0, 99]
        void encode_after_touch_controller_range(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 99> data);

        /// @brief Encodes after touch assign parameter change message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data After touch assign. In range [0, 7]
        void encode_after_touch_controller_assign(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 7> data);

        /// @brief Encodes a panel VOICE button press/release message (selects voice number).
        /// Emulates the front-panel VOICE [1–32] buttons
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param voice Voice index. In range [0, 31]
        /// @param data true for press, false for release
        void encode_button_voice(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 31> voice,
            const bool data);

        /// @brief Encodes a panel STORE button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_store(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel MEMORY PROTECT (INTERNAL) toggle press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_memory_protect_internal(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel MEMORY PROTECT (CARTRIDGE) toggle press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_memory_protect_cartridge(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel OPERATOR SELECT button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_op_select(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel EDIT/COMPARE button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_edit_compare(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel MEMORY SELECT (INTERNAL) press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_memory_select_internal(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel MEMORY SELECT (CARTRIDGE) press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_memory_select_cartridge(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel FUNCTION button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_function(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel NO button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_no(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a panel YES button press/release message
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data true for press, false for release
        void encode_button_yes(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const bool data);

        /// @brief Encodes a patch SysEx data block.
        /// Appends a complete 155 byte voice for the current patch slot
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Patch parameters to encode
        void encode_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const patch& data);

        /// @brief Encodes a 32 patches bank SysEx data block
        /// Appends a complete internal bank (32 patches)
        /// @param encoded Vector to append the encoded SysEx message to
        /// @param device Target device number. In range [0, 15]
        /// @param data Array of 32 patches to encode
        void encode_bank(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const std::array<patch, 32>& data);

        /// @brief Decodes a 32 patches bank SysEx data block.
        /// Parses an internal bank (32 patches) into structured data
        /// @param encoded Vector to decode the SysEx message from
        /// @param device Expected target device number. In range [0, 15]
        /// @param data Output array to receive the 32 decoded patches
        /// @return true on success
        bool decode_bank(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            std::array<patch, 32>& data);

    }
}
}
