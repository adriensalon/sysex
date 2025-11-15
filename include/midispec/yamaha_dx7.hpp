#pragma once

#include <array>
#include <vector>

#include <midispec/core/capabilities.hpp>
#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Yamaha DX7 synthesizer.
/// To allow SysEx, edit FUNCTION > 8 to show SYS INFO AVAIL.
/// It can receive SysEx for a patch or a 32 patches bank (entire internal memory).
/// It can only send the current 32 patches bank by editing FUNCTION > 8 to show MIDI TRANSMIT?.
/// A workaround by sending these commands from SysEx is demonstrated in the 'test/gtest_yamaha_dx7.cpp' file.
struct yamaha_dx7 {

    struct voice_patch {
        std::array<char, 10> voice_name;
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
        std::array<integral<std::uint8_t, 0, 3>, 6> op_keyboard_scaling_left_curve;
        std::array<integral<std::uint8_t, 0, 3>, 6> op_keyboard_scaling_right_curve;
        std::array<integral<std::uint8_t, 0, 7>, 6> op_keyboard_scaling_rate;
        std::array<integral<std::uint8_t, 0, 3>, 6> op_amplitude_modulation_sensitivity;
        std::array<integral<std::uint8_t, 0, 7>, 6> op_velocity_sensitivity;
        std::array<integral<std::uint8_t, 0, 99, 99>, 6> op_output_level;
        std::array<integral<std::uint8_t, 0, 1>, 6> op_oscillator_mode;
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
        integral<std::uint8_t, 0, 1> oscillator_key_sync;
        integral<std::uint8_t, 0, 4> lfo_waveform_mode;
        integral<std::uint8_t, 0, 99> lfo_speed;
        integral<std::uint8_t, 0, 99> lfo_delay;
        integral<std::uint8_t, 0, 99> lfo_pitch_modulation_depth;
        integral<std::uint8_t, 0, 99> lfo_amplitude_modulation_depth;
        integral<std::uint8_t, 0, 1> lfo_sync;
        integral<std::uint8_t, 0, 7> pitch_modulation_sensitivity;
        integral<std::uint8_t, 0, 48, 24> transpose_semitones;
    };

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

    /// @brief Encodes a program change message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param program MIDI program clamped for the DX7. In range [0, 31]
    static void encode_program_change(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint8_t, 0, 31> program);

    /// @brief Decodes a program change message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param program MIDI program clamped for the DX7. In range [0, 31]
    /// @return true on success
    static bool decode_program_change(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 31>& program);

    /// @brief Encodes a pitchbend change message
    /// @param encoded Vector to append the encoded message to
    /// @param channel Target channel number. In range [0, 15]
    /// @param pitchbend MIDI pitchbend. In range [0, 16383] (Default 8192)
    static void encode_pitchbend_change(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> channel,
        const integral<std::uint16_t, 0, 16383, 8192> pitchbend);

    /// @brief Decodes a pitchbend change message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param pitchbend MIDI pitchbend. In range [0, 16383] (Default 8192)
    /// @return true on success
    static bool decode_pitchbend_change(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint16_t, 0, 16383, 8192>& pitchbend);

    /// @brief Decodes a channel pressure (mono after touch) message
    /// @param encoded Vector to read the encoded message from
    /// @param channel Target channel number. In range [0, 15]
    /// @param program Nonstandard MIDI channel pressure. In range [0, 127]
    /// @return true on success
    static bool decode_channel_pressure(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& channel,
        integral<std::uint8_t, 0, 127>& pressure);

    // system exclusive

    /// @brief Encodes an operator envelope generator rate 1 (attack rate) parameter change message.
    /// This parameter applies to the current patch for the selected operator
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param op Operator index. In range [0, 5]
    /// @param data Envelope generator rate 1. In range [0, 99]
    static void encode_op_envelope_generator_rate_1(
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
    static void encode_op_envelope_generator_rate_2(
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
    static void encode_op_envelope_generator_rate_3(
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
    static void encode_op_envelope_generator_rate_4(
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
    static void encode_op_envelope_generator_level_1(
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
    static void encode_op_envelope_generator_level_2(
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
    static void encode_op_envelope_generator_level_3(
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
    static void encode_op_envelope_generator_level_4(
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
    static void encode_op_keyboard_scaling_breakpoint(
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
    static void encode_op_keyboard_scaling_left_depth(
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
    static void encode_op_keyboard_scaling_right_depth(
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
    static void encode_op_keyboard_scaling_left_curve(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 3> data);

    /// @brief Encodes an operator keyboard scaling right curve parameter change message.
    /// This parameter applies to the current patch for the selected operator
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param op Operator index. In range [0, 5]
    /// @param data Right curve (see op_keyboard_scaling_curve)
    static void encode_op_keyboard_scaling_right_curve(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 3> data);

    /// @brief Encodes an operator keyboard scaling rate (key rate scaling) parameter change message.
    /// This parameter applies to the current patch for the selected operator
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param op Operator index. In range [0, 5]
    /// @param data Rate scaling. In range [0, 7]
    static void encode_op_keyboard_scaling_rate(
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
    static void encode_op_amplitude_modulation_sensitivity(
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
    static void encode_op_velocity_sensitivity(
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
    static void encode_op_output_level(
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
    static void encode_op_oscillator_mode(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes an operator oscillator coarse parameter change message.
    /// This parameter applies to the current patch for the selected operator
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param op Operator index. In range [0, 5]
    /// @param data Coarse frequency. In range [0, 31]
    static void encode_op_oscillator_coarse(
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
    static void encode_op_oscillator_fine(
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
    static void encode_op_oscillator_detune(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 14, 7> data);

    /// @brief Encodes pitch envelope generator rate 1 (attack) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG rate 1. In range [0, 99]
    static void encode_pitch_envelope_rate_1(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator rate 2 (decay 1) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG rate 2. In range [0, 99]
    static void encode_pitch_envelope_rate_2(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator rate 3 (decay 2) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG rate 3. In range [0, 99]
    static void encode_pitch_envelope_rate_3(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator rate 4 (release) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG rate 4. In range [0, 99]
    static void encode_pitch_envelope_rate_4(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator level 1 parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param op Operator index. In range [0, 5]
    /// @param data Pitch EG level 1. In range [0, 99]
    static void encode_pitch_envelope_level_1(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator level 2 parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG level 2. In range [0, 99]
    static void encode_pitch_envelope_level_2(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator level 3 parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG level 2. In range [0, 99]
    static void encode_pitch_envelope_level_3(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes pitch envelope generator level 4 parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Pitch EG level 2. In range [0, 99]
    static void encode_pitch_envelope_level_4(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes algorithm (operator routing) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Algorithm number. In range [0, 31]
    static void encode_algorithm_mode(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 31> data);

    /// @brief Encodes algorithm feedback amount parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Feedback. In range [0, 7]
    static void encode_algorithm_feedback(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes oscillator key sync enable/disable parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true to enable, false to disable
    static void encode_oscillator_key_sync(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes LFO waveform parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data LFO waveform (see lfo_waveform_mode)
    static void encode_lfo_waveform(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 4> data);

    /// @brief Encodes LFO speed parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data LFO speed. In range [0, 99]
    static void encode_lfo_speed(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes LFO delay parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data LFO delay. In range [0, 99]
    static void encode_lfo_delay(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes LFO pitch modulation depth parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data PMD (pitch modulation depth). In range [0, 99]
    static void encode_lfo_pitch_modulation_depth(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes LFO amplitude modulation depth parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data AMD (amplitude modulation depth). In range [0, 99]
    static void encode_lfo_amplitude_modulation_depth(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes LFO sync on key-on enable/disable parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true to enable, false to disable
    static void encode_lfo_sync(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes pitch modulation sensitivity (global) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data PMS (pitch modulation sensitivity). In range [0, 7]
    static void encode_pitch_modulation_sensitivity(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes transpose (coarse tune in semitones) parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Transpose semitones. In range [-24, 24] (0 = concert)
    static void encode_transpose_semitones(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 48, 24> data);

    /// @brief Encodes operator enable mask parameter change message.
    /// Each bit enables/disables one operator (OP1..OP6).
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Bitmask for operators. In range [0x00, 0x3F] (Default 0x3F = all on)
    static void encode_op_enable_mask(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0x00, 0x3F, 0x3F> data);

    /// @brief Encodes patch name parameter change message.
    /// This parameter applies to the current patch
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data 10-character patch name (ASCII)
    static void encode_patch_name(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const std::array<char, 10>& data);

    /// @brief Encodes mono mode enable/disable parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data false for mono, true for poly
    static void encode_mono_poly_mode(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes pitchbend range (semitones) parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Upward bend range. In range [0, 12] (Default 2)
    static void encode_pitchbend_range_semitones(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 12, 2> data);

    /// @brief Encodes pitchbend step parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Downward bend step. In range [0, 12]
    static void encode_pitchbend_step(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 12> data);

    /// @brief Encodes portamento mode parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Portamento mode. In range [0, 1]
    static void encode_portamento_mode(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes portamento glissando mode enable/disable parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true to enable, false to disable
    static void encode_portamento_glissando(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes portamento time parameter change message.
    /// This parameter applies to the current patch (performance behavior)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Portamento time. In range [0, 99]
    static void encode_portamento_time(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes modulation wheel range parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Modulation wheel range. In range [0, 99]
    static void encode_modulation_wheel_range(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes modulation wheel assign parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Modulation wheel assign. In range [0, 7]
    static void encode_modulation_wheel_assign(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes foot controller range parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Foot controller range. In range [0, 99]
    static void encode_foot_controller_range(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes foot controller assign parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Foot controller assign. In range [0, 7]
    static void encode_foot_controller_assign(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes breath controller range parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Breath controller range. In range [0, 99]
    static void encode_breath_controller_range(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes breath controller assign parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Breath controller assign. In range [0, 7]
    static void encode_breath_controller_assign(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes aftertouch range parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Aftertouch controller range. In range [0, 99]
    static void encode_aftertouch_controller_range(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes aftertouch assign parameter change message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Aftertouch assign. In range [0, 7]
    static void encode_aftertouch_controller_assign(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 7> data);

    /// @brief Encodes a panel VOICE button press/release message (selects voice number).
    /// Emulates the front-panel VOICE [1–32] buttons
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param voice Voice index. In range [0, 31]
    /// @param data true for press, false for release
    static void encode_button_voice(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 31> voice,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel STORE button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_store(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel MEMORY PROTECT (INTERNAL) toggle press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_memory_protect_internal(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel MEMORY PROTECT (CARTRIDGE) toggle press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_memory_protect_cartridge(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel OPERATOR SELECT button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_op_select(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel EDIT/COMPARE button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_edit_compare(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel MEMORY SELECT (INTERNAL) press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_memory_select_internal(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel MEMORY SELECT (CARTRIDGE) press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_memory_select_cartridge(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel FUNCTION button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_function(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel NO button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_no(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a panel YES button press/release message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data true for press, false for release
    static void encode_button_yes(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 1> data);

    /// @brief Encodes a patch SysEx data block.
    /// Appends a complete 155 byte voice for the current patch slot
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Patch parameters to encode
    static void encode_voice_patch(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const voice_patch& data);

    /// @brief Encodes a 32 patches bank SysEx data block
    /// Appends a complete internal bank (32 patches)
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 15]
    /// @param data Array of 32 patches to encode
    static void encode_voice_patch_bank(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const std::array<voice_patch, 32>& data);

    /// @brief Decodes a 32 patches bank SysEx data block.
    /// Parses an internal bank (32 patches) into structured data
    /// @param encoded Vector to decode the SysEx message from
    /// @param device Expected target device number. In range [0, 15]
    /// @param data Output array to receive the 32 decoded patches
    /// @return true on success
    static bool decode_voice_patch_bank(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 15>& device,
        std::array<voice_patch, 32>& data);
};
}
