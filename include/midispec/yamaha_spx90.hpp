#pragma once

#include <array>
#include <variant>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {
    
/// @brief MIDI support for the Yamaha DX7.
/// To reveive SysEx from the hardware internal wiring to MIDI THRU and MIDI OUT
/// must be switched by opening and modifying the hardware.
namespace yamaha_spx90 {

    enum struct lfo_waveform : std::uint8_t {
        sine = 0,
        triangle = 1,
        square = 2,
        saw_up = 3,
        saw_down = 4,
    };

    enum struct freeze_trigger_mode : std::uint8_t {
        manual = 0,
        midi = 1,
        level = 2,
        automatic = 3,
    };

    enum struct stereo_mode : std::uint8_t {
        mono = 0,
        stereo = 1,
        ping_pong = 2,
    };

    enum struct phase_relation : std::uint8_t {
        in_phase = 0,
        quarter_turn = 1,
        half_turn = 2,
    };

    enum struct tone_curve_mode : std::uint8_t {
        low_pass = 0,
        high_pass = 1,
    };

    struct reverb_hall_parameters {
        integral<std::uint8_t, 0, 99> time;
        integral<std::uint8_t, 0, 99> high;
        integral<std::uint8_t, 0, 99> delay;
        integral<std::uint8_t, 0, 99> high_pass_filter;
        integral<std::uint8_t, 0, 99> low_pass_filter;
    };

    struct reverb_room_parameters {
        integral<std::uint8_t, 0, 99> time;
        integral<std::uint8_t, 0, 99> high;
        integral<std::uint8_t, 0, 99> pre_delay;
        integral<std::uint8_t, 0, 99> room_size;
        integral<std::uint8_t, 0, 99> low_pass_filter;
    };

    struct reverb_plate_parameters {
        integral<std::uint8_t, 0, 99> time;
        integral<std::uint8_t, 0, 99> high;
        integral<std::uint8_t, 0, 99> pre_delay;
        integral<std::uint8_t, 0, 99> diffusion;
        integral<std::uint8_t, 0, 99> low_pass_filter;
    };

    struct early_reflections_parameters {
        // er_pattern pattern; // 0..7 (or wider if confirmed)
        integral<std::uint8_t, 0, 99> delay; // ~1..100 ms (UI)
        integral<std::uint8_t, 0, 99> room_size; // 0..99
        integral<std::uint8_t, 0, 99> low_pass_filter; // tone
    };

    struct gate_reverb_parameters {
        integral<std::uint8_t, 0, 99> gate_time; // ms scale
        integral<std::uint8_t, 0, 99> character; // envelope/shape
        integral<std::uint8_t, 0, 99> pre_delay; // ms
        integral<std::uint8_t, 0, 99> low_pass_filter;
    };

    struct chorus_parameters {
        integral<std::uint8_t, 0, 99> speed; // Hz (UI)
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay; // base delay in ms
        phase_relation phase; // inter-channel phase
    };

    struct flanger_parameters {
        integral<std::uint8_t, 0, 99> speed; // Hz
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay; // very short ms
        integral<std::uint8_t, 0, 99> feedback_gain; // regeneration
        integral<std::uint8_t, 0, 99> manual; // static offset
    };

    struct phaser_parameters {
        integral<std::uint8_t, 0, 99> speed; // Hz
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay_time; // ~0.1..8.0 ms (UI)
        integral<std::uint8_t, 0, 99> feedback_gain; // if exposed
    };

    struct tremolo_parameters {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
    };

    struct vibrato_parameters {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
    };

    struct symphonic_parameters {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> detune;
    };

    struct delay_parameters {
        stereo_mode mode; // mono/stereo/ping-pong
        integral<std::uint8_t, 0, 99> delay_time; // ms (algorithm may scale up)
        integral<std::uint8_t, 0, 99> feedback;
        integral<std::uint8_t, 0, 99> hpf; // tone
        integral<std::uint8_t, 0, 99> low_pass_filter; // tone
        integral<std::uint8_t, 0, 99> mod_speed; // Hz (if available)
        integral<std::uint8_t, 0, 99> mod_depth;
    };

    struct echo_parameters {
        stereo_mode mode; // mono/stereo/ping-pong
        integral<std::uint8_t, 0, 99> delay_time_l;
        integral<std::uint8_t, 0, 99> delay_time_r;
        integral<std::uint8_t, 0, 99> feedback;
        integral<std::uint8_t, 0, 99> low_pass_filter;
    };

    struct pitch_change_parameters {
        integral<std::int8_t, -12, 12, 0> coarse; // semitones
        integral<std::int16_t, -100, 100, 0> fine; // cents
        integral<std::uint8_t, 0, 99> delay; // ms before shifted signal
        integral<std::uint8_t, 0, 99> tone; // LP/HP tilt for shifted voice
    };

    struct freeze_parameters {
        freeze_trigger_mode trigger_mode; // manual/midi/level/auto
        integral<std::uint8_t, 0, 99> length; // capture length (scaled)
        integral<std::uint8_t, 0, 99> lowpass; // tone
    };

    using program_parameters = std::variant<
        reverb_hall_parameters,
        reverb_room_parameters,
        reverb_plate_parameters,
        early_reflections_parameters,
        gate_reverb_parameters,
        chorus_parameters,
        flanger_parameters,
        phaser_parameters,
        tremolo_parameters,
        vibrato_parameters,
        symphonic_parameters,
        delay_parameters,
        echo_parameters,
        pitch_change_parameters,
        freeze_parameters>;

    struct program {
        program_parameters parameters;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    namespace channel_voice {

        /// @brief 
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_program_change(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief 
        /// Only affects PITCH CHANGE and FREEZE B programs.
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_note_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);

        /// @brief 
        /// Only affects PITCH CHANGE and FREEZE B programs.
        /// @param encoded 
        /// @param channel 
        /// @param data 
        void encode_note_on(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> data);
    }

    namespace system_exclusive {

        /// @brief 
        /// Corrresponds to the b-3 spec in the user manual
        /// @param encoded 
        /// @param device 
        /// @param bank 
        void encode_bank_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const integral<std::uint8_t, 0, 3> bank);

        /// @brief 
        /// Corrresponds to the b-1 spec in the user manual
        /// @param encoded 
        /// @param device 
        /// @param slot 
        /// @param data 
        /// @return 
        bool decode_parameters(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            integral<std::uint8_t, 0, 89>& slot,
            program_parameters& data);

        /// @brief 
        /// Corrresponds to the b-2 spec in the user manual
        /// @param encoded 
        /// @param device 
        /// @param bank 
        /// @param data 
        /// @return 
        bool decode_bank(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            integral<std::uint8_t, 0, 3>& bank,
            std::array<program, 30>& data);
    }
}
}
