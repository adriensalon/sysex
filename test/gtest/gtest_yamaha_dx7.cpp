#include <tuple>

#include <midispec/test/gtest.hpp>
#include <midispec/spec/yamaha_dx7.hpp>

namespace midispec {

    static bool operator==(const yamaha_dx7::voice_patch& first, const yamaha_dx7::voice_patch& second)
    {
        return (first.op_envelope_generator_rate_1 == second.op_envelope_generator_rate_1) && (first.op_envelope_generator_rate_2 == second.op_envelope_generator_rate_2) && (first.op_envelope_generator_rate_3 == second.op_envelope_generator_rate_3) && (first.op_envelope_generator_rate_4 == second.op_envelope_generator_rate_4) && (first.op_envelope_generator_level_1 == second.op_envelope_generator_level_1) && (first.op_envelope_generator_level_2 == second.op_envelope_generator_level_2) && (first.op_envelope_generator_level_3 == second.op_envelope_generator_level_3) && (first.op_envelope_generator_level_4 == second.op_envelope_generator_level_4) && (first.op_keyboard_scaling_breakpoint == second.op_keyboard_scaling_breakpoint) && (first.op_keyboard_scaling_left_depth == second.op_keyboard_scaling_left_depth) && (first.op_keyboard_scaling_right_depth == second.op_keyboard_scaling_right_depth) && (first.op_keyboard_scaling_left_curve == second.op_keyboard_scaling_left_curve) && (first.op_keyboard_scaling_right_curve == second.op_keyboard_scaling_right_curve) && (first.op_keyboard_scaling_rate == second.op_keyboard_scaling_rate) && (first.op_amplitude_modulation_sensitivity == second.op_amplitude_modulation_sensitivity) && (first.op_velocity_sensitivity == second.op_velocity_sensitivity) && (first.op_output_level == second.op_output_level) && (first.op_oscillator_mode == second.op_oscillator_mode) && (first.op_oscillator_coarse == second.op_oscillator_coarse) && (first.op_oscillator_fine == second.op_oscillator_fine) && (first.op_oscillator_detune == second.op_oscillator_detune) && (first.pitch_envelope_rate_1 == second.pitch_envelope_rate_1) && (first.pitch_envelope_rate_2 == second.pitch_envelope_rate_2) && (first.pitch_envelope_rate_3 == second.pitch_envelope_rate_3) && (first.pitch_envelope_rate_4 == second.pitch_envelope_rate_4) && (first.pitch_envelope_level_1 == second.pitch_envelope_level_1) && (first.pitch_envelope_level_2 == second.pitch_envelope_level_2) && (first.pitch_envelope_level_3 == second.pitch_envelope_level_3) && (first.pitch_envelope_level_4 == second.pitch_envelope_level_4) && (first.algorithm_mode == second.algorithm_mode) && (first.algorithm_feedback == second.algorithm_feedback) && (first.oscillator_key_sync == second.oscillator_key_sync) && (first.lfo_waveform_mode == second.lfo_waveform_mode) && (first.lfo_speed == second.lfo_speed) && (first.lfo_delay == second.lfo_delay) && (first.lfo_pitch_modulation_depth == second.lfo_pitch_modulation_depth) && (first.lfo_amplitude_modulation_depth == second.lfo_amplitude_modulation_depth) && (first.lfo_sync == second.lfo_sync) && (first.pitch_modulation_sensitivity == second.pitch_modulation_sensitivity) && (first.transpose_semitones == second.transpose_semitones) && (first.voice_name == second.voice_name);
    }

    static bool operator!=(const yamaha_dx7::voice_patch& first, const yamaha_dx7::voice_patch& second)
    {
        return !(first == second);
    }

    struct test_yamaha_dx7 : public test_gtest {

        inline static std::mt19937 random_device;

        void save_to_voice(const integral<std::uint8_t, 0, 15> device, const integral<std::uint8_t, 0, 31> voice)
        {
            std::vector<std::uint8_t> _sent;

            yamaha_dx7::encode_button_memory_select_internal(_sent, device, 1);
            send(_sent);
            yamaha_dx7::encode_button_memory_select_internal(_sent, device, 0);
            send(_sent);
            yamaha_dx7::encode_button_store(_sent, device, 1);
            send(_sent);
            yamaha_dx7::encode_button_voice(_sent, device, voice, 1);
            send(_sent);
            yamaha_dx7::encode_button_voice(_sent, device, voice, 0);
            send(_sent);
            yamaha_dx7::encode_button_store(_sent, device, 0);
            send(_sent);
        }

        void transmit_bank_read_voice(const integral<std::uint8_t, 0, 15> device, const integral<std::uint8_t, 0, 31> voice, yamaha_dx7::voice_patch& data)
        {
            std::vector<std::uint8_t> _sent;
            std::vector<std::uint8_t> _received;
            std::array<yamaha_dx7::voice_patch, 32> _bank;
            integral<std::uint8_t, 0, 15> _received_device;

            yamaha_dx7::encode_button_function(_sent, device, 1);
            send(_sent);
            yamaha_dx7::encode_button_function(_sent, device, 0);
            send(_sent);
            yamaha_dx7::encode_button_voice(_sent, device, 0, 1);
            send(_sent);
            yamaha_dx7::encode_button_voice(_sent, device, 0, 0);
            send(_sent);
            for (std::size_t _index = 0; _index < 3; ++_index) {
                yamaha_dx7::encode_button_voice(_sent, device, 7, 1);
                send(_sent);
                yamaha_dx7::encode_button_voice(_sent, device, 7, 0);
                send(_sent);
            }
            yamaha_dx7::encode_button_yes(_sent, device, 1);
            send(_sent);
            yamaha_dx7::encode_button_yes(_sent, device, 0);
            send(_sent);

            EXPECT_TRUE(receive(_received));
            EXPECT_TRUE(yamaha_dx7::decode_voice_patch_bank(_received, _received_device, _bank));
            EXPECT_EQ(device, _received_device);
            data = _bank[voice.value()];
        }
    };

    TEST_F(test_yamaha_dx7, op_envelope_generator_rate_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_rate_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_1[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_rate_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_1[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_rate_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_1[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_rate_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_rate_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_2[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_rate_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_2[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_rate_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_2[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_rate_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_rate_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_3[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_rate_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_3[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_rate_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_3[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_rate_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_rate_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_4[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_rate_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_4[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_rate_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_rate_4[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_level_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_level_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_1[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_level_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_1[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_level_1(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_1[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_level_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_level_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_2[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_level_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_2[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_level_2(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_2[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_level_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_level_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_3[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_level_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_3[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_level_3(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_3[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_envelope_generator_level_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_envelope_generator_level_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_4[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_envelope_generator_level_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_4[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_envelope_generator_level_4(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_envelope_generator_level_4[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_breakpoint)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_breakpoint(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_breakpoint[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_breakpoint(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_breakpoint[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_breakpoint(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_breakpoint[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_left_depth)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_left_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_depth[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_left_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_depth[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_left_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_depth[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_right_depth)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_right_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_depth[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_right_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_depth[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_right_depth(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_depth[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_left_curve)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 3> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_left_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_curve[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_left_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_curve[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_left_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_left_curve[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_right_curve)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 3> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_right_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_curve[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_right_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_curve[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_right_curve(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_right_curve[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_keyboard_scaling_rate)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 7> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_keyboard_scaling_rate(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_rate[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_keyboard_scaling_rate(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_rate[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_keyboard_scaling_rate(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_keyboard_scaling_rate[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_amplitude_modulation_sensitivity)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 3> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_amplitude_modulation_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_amplitude_modulation_sensitivity[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_amplitude_modulation_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_amplitude_modulation_sensitivity[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_amplitude_modulation_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_amplitude_modulation_sensitivity[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_velocity_sensitivity)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 7> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_velocity_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_velocity_sensitivity[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_velocity_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_velocity_sensitivity[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_velocity_sensitivity(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_velocity_sensitivity[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_output_level)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_output_level(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_output_level[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_output_level(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_output_level[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_output_level(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_output_level[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, oscillator_mode)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 1> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_oscillator_mode(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_mode[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_oscillator_mode(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_mode[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_oscillator_coarse)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 31> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_oscillator_coarse(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_coarse[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_oscillator_coarse(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_coarse[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_oscillator_coarse(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_coarse[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_oscillator_fine)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_oscillator_fine(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_fine[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_oscillator_fine(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_fine[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_oscillator_fine(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_fine[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, op_oscillator_detune)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 14, 7> _data;
        yamaha_dx7::voice_patch _voice_data;

        _op = _op.min_value;
        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_op_oscillator_detune(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_detune[_op.value()]);

        _op = _op.from_random(random_device);
        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_op_oscillator_detune(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_detune[_op.value()]);

        _op = _op.max_value;
        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_op_oscillator_detune(_encoded, _device, _op, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.op_oscillator_detune[_op.value()]);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_rate_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_rate_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_1);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_rate_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_1);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_rate_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_1);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_rate_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_rate_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_2);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_rate_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_2);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_rate_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_2);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_rate_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_rate_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_3);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_rate_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_3);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_rate_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_3);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_rate_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_rate_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_4);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_rate_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_4);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_rate_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_rate_4);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_level_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_level_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_1);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_level_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_1);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_level_1(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_1);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_level_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_level_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_2);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_level_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_2);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_level_2(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_2);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_level_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_level_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_3);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_level_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_3);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_level_3(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_3);
    }

    TEST_F(test_yamaha_dx7, pitch_envelope_level_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_envelope_level_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_4);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_envelope_level_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_4);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_envelope_level_4(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_envelope_level_4);
    }

    TEST_F(test_yamaha_dx7, algorithm_mode)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 31> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_algorithm_mode(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_mode);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_algorithm_mode(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_mode);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_algorithm_mode(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_mode);
    }

    TEST_F(test_yamaha_dx7, algorithm_feedback)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 7> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_algorithm_feedback(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_feedback);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_algorithm_feedback(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_feedback);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_algorithm_feedback(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.algorithm_feedback);
    }

    TEST_F(test_yamaha_dx7, oscillator_key_sync)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 1> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_oscillator_key_sync(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.oscillator_key_sync);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_oscillator_key_sync(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.oscillator_key_sync);
    }

    TEST_F(test_yamaha_dx7, lfo_waveform)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 4> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_waveform(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_waveform_mode);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_lfo_waveform(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_waveform_mode);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_waveform(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_waveform_mode);
    }

    TEST_F(test_yamaha_dx7, lfo_speed)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_speed(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_speed);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_lfo_speed(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_speed);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_speed(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_speed);
    }

    TEST_F(test_yamaha_dx7, lfo_delay)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_delay(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_delay);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_lfo_delay(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_delay);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_delay(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_delay);
    }

    TEST_F(test_yamaha_dx7, lfo_pitch_modulation_depth)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_pitch_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_pitch_modulation_depth);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_lfo_pitch_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_pitch_modulation_depth);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_pitch_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_pitch_modulation_depth);
    }

    TEST_F(test_yamaha_dx7, lfo_amplitude_modulation_depth)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 99> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_amplitude_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_amplitude_modulation_depth);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_lfo_amplitude_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_amplitude_modulation_depth);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_amplitude_modulation_depth(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_amplitude_modulation_depth);
    }

    TEST_F(test_yamaha_dx7, lfo_sync)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 1> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_lfo_sync(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_sync);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_lfo_sync(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.lfo_sync);
    }

    TEST_F(test_yamaha_dx7, pitch_modulation_sensitivity)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 7> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_pitch_modulation_sensitivity(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_modulation_sensitivity);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_pitch_modulation_sensitivity(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_modulation_sensitivity);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_pitch_modulation_sensitivity(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.pitch_modulation_sensitivity);
    }

    TEST_F(test_yamaha_dx7, transpose_semitones)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        integral<std::uint8_t, 0, 48, 24> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.min_value;
        _data = _data.min_value;
        yamaha_dx7::encode_transpose_semitones(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.transpose_semitones);

        _voice = _voice.from_random(random_device);
        _data = _data.from_random(random_device);
        yamaha_dx7::encode_transpose_semitones(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.transpose_semitones);

        _voice = _voice.max_value;
        _data = _data.max_value;
        yamaha_dx7::encode_transpose_semitones(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.transpose_semitones);
    }

    TEST_F(test_yamaha_dx7, voice_name)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        std::array<char, 10> _data;
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.from_random(random_device);
        _data = { 'T', 'E', 'S', 'T', ' ', 'S', 'Y', 'S', 'E', 'X' };
        yamaha_dx7::encode_patch_name(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data.voice_name);
    }

    TEST_F(test_yamaha_dx7, voice_patch)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        yamaha_dx7::voice_patch _data = {};
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.from_random(random_device);
        _data.voice_name = { 'T', 'E', 'S', 'T', ' ', 'S', 'Y', 'S', 'E', 'X' };
        yamaha_dx7::encode_voice_patch(_encoded, _device, _data);
        send(_encoded);
        save_to_voice(_device, _voice);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data, _voice_data);
    }

    TEST_F(test_yamaha_dx7, bank)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _voice;
        std::array<yamaha_dx7::voice_patch, 32> _data = {};
        yamaha_dx7::voice_patch _voice_data;

        _voice = _voice.from_random(random_device);
        _data[_voice.value()].voice_name = { 'T', 'E', 'S', 'T', ' ', 'S', 'Y', 'S', 'E', 'X' };
        yamaha_dx7::encode_voice_patch_bank(_encoded, _device, _data);
        send(_encoded);
        transmit_bank_read_voice(_device, _voice, _voice_data);
        EXPECT_EQ(_data[_voice.value()], _voice_data);
    }

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}