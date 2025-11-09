#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <sysex/core/parameter.hpp>

namespace sysex {

/// @brief
namespace yamaha_dx7 {

    namespace tag {
        struct device_id {};
        struct voice_id {};
        struct op_id {};
        struct op_eg_rate_1 {};
        struct op_eg_rate_2 {};
        struct op_eg_rate_3 {};
        struct op_eg_rate_4 {};
        struct op_eg_level_1 {};
        struct op_eg_level_2 {};
        struct op_eg_level_3 {};
        struct op_eg_level_4 {};
        struct op_keyboard_scaling_breakpoint {};
        struct op_keyboard_scaling_left_depth {};
        struct op_keyboard_scaling_right_depth {};
        struct op_keyboard_scaling_left_curve {};
        struct op_keyboard_scaling_right_curve {};
        struct op_keyboard_scaling_rate {};
        struct op_amplitude_modulation_sensitivity {};
        struct op_velocity_sensitivity {};
        struct op_output_level {};
        struct op_oscillator_mode {};
        struct op_oscillator_coarse {};
        struct op_oscillator_fine {};
        struct op_oscillator_detune {};
        struct pitch_envelope_rate_1 {};
        struct pitch_envelope_rate_2 {};
        struct pitch_envelope_rate_3 {};
        struct pitch_envelope_rate_4 {};
        struct pitch_envelope_level_1 {};
        struct pitch_envelope_level_2 {};
        struct pitch_envelope_level_3 {};
        struct pitch_envelope_level_4 {};
        struct algorithm_mode {};
        struct algorithm_feedback {};
        struct oscillator_key_sync {};
        struct button_1 {};
        struct button_2 {};
        struct button_3 {};
        struct button_4 {};
        struct button_5 {};
        struct button_6 {};
        struct button_7 {};
        struct button_8 {};
        struct button_store {};
        struct button_memory_protect_internal {};
        struct button_memory_protect_cartridge {};
        struct button_memory_select_internal {};
        struct button_memory_select_cartridge {};
        struct button_function {};
        struct button_no {};
        struct button_yes {};
    };

    /// @brief Named keyboard level-scaling curve.
    /// Range is [0, 3]
    enum struct curve : std::uint8_t {
        neg_lin = 0,
        pos_lin = 1,
        neg_exp = 2,
        pos_exp = 3
    };

    /// @brief Named oscillator mode.
    /// Range is [0, 1]
    enum struct oscillator_mode : std::uint8_t {
        ratio = 0,
        fixed = 1
    };

    /// @brief Named LFO waveform.
    /// Range is [0, 5]
    enum struct lfo_waveform : std::uint8_t {
        triangle = 0,
        saw_down = 1,
        saw_up = 2,
        square = 3,
        sine = 4,
        sample_hold = 5
    };

    /// @brief Named hardware unit. Device can be selected directly on the hardware.
    /// Some hardware can be configured to receive messages from all devices.
    /// Devices can be used to link multiple hardware units to a single MIDI input or output.
    /// Range is [0, 15]
    using device_id = sysex::parameter<tag::device_id, std::uint8_t, 0, 15>;

    /// @brief
    /// Range is [0, 31]
    using voice_id = sysex::parameter<tag::device_id, std::uint8_t, 0, 31>;

    /// @brief
    /// Range is [0, 5]
    using op_id = sysex::parameter<tag::op_id, std::uint8_t, 0, 5>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_rate_1 = sysex::parameter<tag::op_eg_rate_1, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_rate_2 = sysex::parameter<tag::op_eg_rate_2, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_rate_3 = sysex::parameter<tag::op_eg_rate_3, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_rate_4 = sysex::parameter<tag::op_eg_rate_4, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_level_1 = sysex::parameter<tag::op_eg_level_1, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_level_2 = sysex::parameter<tag::op_eg_level_2, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_level_3 = sysex::parameter<tag::op_eg_level_3, std::uint8_t, 0, 99>;

    /// @brief
    /// Range is [0, 99]
    using op_eg_level_4 = sysex::parameter<tag::op_eg_level_4, std::uint8_t, 0, 99>;

    /// @brief
    using op_keyboard_scaling_breakpoint = sysex::parameter<tag::op_keyboard_scaling_breakpoint, std::uint8_t, 0, 99>;

    /// @brief
    using op_keyboard_scaling_left_depth = sysex::parameter<tag::op_keyboard_scaling_left_depth, std::uint8_t, 0, 99>;

    /// @brief
    using op_keyboard_scaling_right_depth = sysex::parameter<tag::op_keyboard_scaling_right_depth, std::uint8_t, 0, 99>;

    /// @brief
    using op_keyboard_scaling_left_curve = sysex::parameter<tag::op_keyboard_scaling_left_curve, curve>;

    /// @brief
    using op_keyboard_scaling_right_curve = sysex::parameter<tag::op_keyboard_scaling_right_curve, curve>;

    /// @brief
    using op_keyboard_scaling_rate = sysex::parameter<tag::op_keyboard_scaling_rate, std::uint8_t, 0, 7>;

    /// @brief
    using op_amplitude_modulation_sensitivity = sysex::parameter<tag::op_amplitude_modulation_sensitivity, std::uint8_t, 0, 3>;

    /// @brief
    using op_velocity_sensitivity = sysex::parameter<tag::op_velocity_sensitivity, std::uint8_t, 0, 7>;

    /// @brief
    using op_output_level = sysex::parameter<tag::op_output_level, std::uint8_t, 0, 99, 99>;

    /// @brief
    using op_oscillator_mode = sysex::parameter<tag::op_oscillator_mode, oscillator_mode>;

    /// @brief
    using op_oscillator_coarse = sysex::parameter<tag::op_oscillator_coarse, std::uint8_t, 0, 31>;

    /// @brief
    using op_oscillator_fine = sysex::parameter<tag::op_oscillator_fine, std::uint8_t, 0, 99>;

    /// @brief
    using op_oscillator_detune = sysex::parameter<tag::op_oscillator_detune, std::int8_t, 0, 14, 0>;

    /// @brief
    using pitch_envelope_rate_1 = sysex::parameter<tag::pitch_envelope_rate_1, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_rate_2 = sysex::parameter<tag::pitch_envelope_rate_2, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_rate_3 = sysex::parameter<tag::pitch_envelope_rate_3, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_rate_4 = sysex::parameter<tag::pitch_envelope_rate_4, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_level_1 = sysex::parameter<tag::pitch_envelope_level_1, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_level_2 = sysex::parameter<tag::pitch_envelope_level_2, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_level_3 = sysex::parameter<tag::pitch_envelope_level_3, std::uint8_t, 0, 99>;

    /// @brief
    using pitch_envelope_level_4 = sysex::parameter<tag::pitch_envelope_level_4, std::uint8_t, 0, 99>;

    /// @brief
    using algorithm_mode = sysex::parameter<tag::algorithm_mode, std::uint8_t, 0, 31>;

    /// @brief
    using algorithm_feedback = sysex::parameter<tag::algorithm_feedback, std::uint8_t, 0, 7>;

    /// @brief 
    using oscillator_key_sync = sysex::parameter<tag::oscillator_key_sync, bool>;

    struct lfo_settings {
        lfo_waveform waveform = lfo_waveform::triangle;
        std::uint8_t speed = 0; // 0..99
        std::uint8_t delay = 0; // 0..99
        std::uint8_t pitch_mod_depth = 0; // 0..99
        std::uint8_t amp_mod_depth = 0; // 0..99
        bool sync = false; // key sync
    };

    struct pitch_modulation_sensitivity {
        std::uint8_t sensitivity; // 0..7
    };

    struct transpose {
        std::int8_t semitones; // typical DX7: -24..+24 semitones (clamped)
    };

    struct op_enable_mask {
        // bit0 = OP1, bit1 = OP2, ... bit5 = OP6 (true=on); bits 6..7 unused
        std::uint8_t mask = 0x3F; // default all on
    };

    struct patch_name {
        std::array<char, 10> name; // ASCII, padded with spaces
    };

    struct single_voice_bulk {
        std::array<op_eg_rate_1, 6> ops_eg_rate_1;
        std::array<op_eg_rate_2, 6> ops_eg_rate_2;
        std::array<op_eg_rate_3, 6> ops_eg_rate_3;
        std::array<op_eg_rate_4, 6> ops_eg_rate_4;
        std::array<op_eg_level_1, 6> ops_eg_level_1;
        std::array<op_eg_level_2, 6> ops_eg_level_2;
        std::array<op_eg_level_3, 6> ops_eg_level_3;
        std::array<op_eg_level_4, 6> ops_eg_level_4;
        std::array<op_keyboard_scaling_breakpoint, 6> ops_keyboard_scaling_breakpoint;
        std::array<op_keyboard_scaling_left_depth, 6> ops_keyboard_scaling_left_depth;
        std::array<op_keyboard_scaling_right_depth, 6> ops_keyboard_scaling_right_depth;
        std::array<op_keyboard_scaling_left_curve, 6> ops_keyboard_scaling_left_curve;
        std::array<op_keyboard_scaling_right_curve, 6> ops_keyboard_scaling_right_curve;
        std::array<op_keyboard_scaling_rate, 6> ops_keyboard_scaling_rate;
        std::array<op_amplitude_modulation_sensitivity, 6> ops_amplitude_modulation_sensitivity;
        std::array<op_velocity_sensitivity, 6> ops_velocity_sensitivity;
        std::array<op_output_level, 6> ops_output_level;
        std::array<op_oscillator_mode, 6> ops_oscillator_mode;
        std::array<op_oscillator_coarse, 6> ops_oscillator_coarse;
        std::array<op_oscillator_fine, 6> ops_oscillator_fine;
        std::array<op_oscillator_detune, 6> ops_oscillator_detune;

        pitch_envelope_rate_1 voice_pitch_envelope_rate_1;
        pitch_envelope_rate_2 voice_pitch_envelope_rate_2;
        pitch_envelope_rate_3 voice_pitch_envelope_rate_3;
        pitch_envelope_rate_4 voice_pitch_envelope_rate_4;
        pitch_envelope_level_1 voice_pitch_envelope_level_1;
        pitch_envelope_level_2 voice_pitch_envelope_level_2;
        pitch_envelope_level_3 voice_pitch_envelope_level_3;
        pitch_envelope_level_4 voice_pitch_envelope_level_4;
        algorithm_mode voice_algorithm_mode;
        algorithm_feedback voice_algorithm_feedback {};
        oscillator_key_sync voice_oscillator_key_sync {};
        lfo_settings voice_lfo_settings {};
        pitch_modulation_sensitivity voice_pitch_modulation_sensitivity;
        transpose voice_transpose;
        op_enable_mask voice_op_enable_mask {}; // live/edit convenience ??
        patch_name voice_patch_name;
    };

    struct bank_bulk {
        std::array<single_voice_bulk, 32> bank_voices;
    };

    // global/system

    struct pitch_bend { // global PB setup
        std::uint8_t up_semitones = 2; // 0..12
        std::uint8_t down_semitones = 2; // 0..12
        std::uint8_t step = 0; // 0..12 (0 = smooth)
    };

    struct portamento {
        bool enabled = false; // on/off
        std::uint8_t time = 0; // 0..99
        bool fingered = false; // fingered portamento mode
        bool glissando = false; // gliss on/off (Mk I step glide)
    };

    struct mono_poly {
        bool mono = false; // mono/poly
        bool unison = false; // unison on/off (Mk I stacks voices)
        std::uint8_t unison_detune = 0; // 0..7 (if applicable)
    };

    struct aftertouch {
        bool enable; // enable/disable AT to voice modulation
    };

    struct foot_controller {
        // DX7 Mk I lets you choose destinations like pitch/amp/bias; exact mapping in .cpp
        bool to_pitch = false;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99 if applicable
    };

    struct breath_controller {
        bool to_pitch = false;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99
    };

    struct mod_wheel {
        bool to_pitch = true;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99
    };

    struct master_tune {
        std::int16_t cents; // typical range about ±100 cents
    };

    struct function_block {
        pitch_bend block_pitch_bend;
        portamento block_portamento;
        mono_poly block_mono_poly;
        aftertouch block_aftertouch;
        foot_controller block_foot_controller;
        breath_controller block_breath_controller;
        mod_wheel block_mod_wheel;
        master_tune block_master_tune;
    };

    
    /// @brief
    /// Range is [0, 1]
    using button_1 = sysex::parameter<tag::button_1, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_2 = sysex::parameter<tag::button_2, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_3 = sysex::parameter<tag::button_3, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_4 = sysex::parameter<tag::button_4, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_5 = sysex::parameter<tag::button_5, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_6 = sysex::parameter<tag::button_6, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_7 = sysex::parameter<tag::button_7, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_8 = sysex::parameter<tag::button_8, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_store = sysex::parameter<tag::button_store, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_memory_protect_internal = sysex::parameter<tag::button_memory_protect_internal, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_memory_protect_cartridge = sysex::parameter<tag::button_memory_protect_cartridge, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_memory_select_internal = sysex::parameter<tag::button_memory_select_internal, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_memory_select_cartridge = sysex::parameter<tag::button_memory_select_cartridge, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_function = sysex::parameter<tag::button_function, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_no = sysex::parameter<tag::button_no, bool>;
    
    /// @brief
    /// Range is [0, 1]
    using button_yes = sysex::parameter<tag::button_yes, bool>;

}

// encode

/// @brief Encodes an op_eg_rate_1 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_1& data);

/// @brief Encodes an op_eg_rate_2 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_2& data);

/// @brief Encodes an op_eg_rate_3 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_3& data);

/// @brief Encodes an op_eg_rate_4 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_4& data);

/// @brief Encodes an op_eg_level_1 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_1& data);

/// @brief Encodes an op_eg_level_2 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_2& data);

/// @brief Encodes an op_eg_level_3 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_3& data);

/// @brief Encodes an op_eg_level_4 parameter change message for the Yamaha DX7
/// @param encoded is the vector to append the encoded sysex message
/// @param device is the device to target
/// @param op is the operator to target
/// @param data is the parameter to encode
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_4& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_breakpoint& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_left_depth& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_right_depth& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_left_curve& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_right_curve& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_keyboard_scaling_rate& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_amplitude_modulation_sensitivity& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_velocity_sensitivity& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_output_level& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_oscillator_mode& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_oscillator_coarse& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_oscillator_fine& data);

/// @brief
/// @param encoded
/// @param device
/// @param op
/// @param data
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_oscillator_detune& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_rate_1& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_rate_2& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_rate_3& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_rate_4& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_level_1& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_level_2& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_level_3& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_envelope_level_4& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::algorithm_mode& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::algorithm_feedback& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::oscillator_key_sync& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::lfo_settings& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_modulation_sensitivity& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::transpose& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_enable_mask& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::patch_name& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::single_voice_bulk& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::bank_bulk& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::pitch_bend& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::portamento& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::mono_poly& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::aftertouch& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::foot_controller& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::breath_controller& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::mod_wheel& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::master_tune& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::function_block& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_1& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_2& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_3& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_4& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_5& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_6& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_7& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_8& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_store& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_protect_internal& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_protect_cartridge& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_select_internal& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_select_cartridge& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_function& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_no& data);
void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_yes& data);

// decode

bool decode(const std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, yamaha_dx7::bank_bulk& data);

}
