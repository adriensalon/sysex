#include <sysex/core/hardware.hpp>
#include <sysex/yamaha_dx7.hpp>

struct yamaha_dx7_hardware : public sysex_hardware {

    inline static constexpr std::chrono::milliseconds debounce_duration = std::chrono::milliseconds(0);
    inline static std::mt19937 random_device = {};

    template <typename... Parameters>
    void encode_and_send(Parameters&&... parameters)
    {
        std::vector<std::uint8_t> _sent;
        sysex::encode(_sent, std::forward<Parameters>(parameters)...);
        send(_sent);
        std::this_thread::sleep_for(debounce_duration);
    }

    void save_to_voice_1(const sysex::yamaha_dx7::device_id device)
    {
        encode_and_send(device, sysex::yamaha_dx7::button_memory_select_internal(true));
        encode_and_send(device, sysex::yamaha_dx7::button_memory_select_internal(false));
        encode_and_send(device, sysex::yamaha_dx7::button_store(true));
        encode_and_send(device, sysex::yamaha_dx7::button_1(true));
        encode_and_send(device, sysex::yamaha_dx7::button_1(false));
        encode_and_send(device, sysex::yamaha_dx7::button_store(false));
    }

    void transmit_bank_read_voice_1(const sysex::yamaha_dx7::device_id device, sysex::yamaha_dx7::single_voice_bulk& voice_1)
    {
        std::vector<std::uint8_t> _received;
        sysex::yamaha_dx7::bank_bulk _received_data;

        encode_and_send(device, sysex::yamaha_dx7::button_function(true));
        encode_and_send(device, sysex::yamaha_dx7::button_function(false));
        encode_and_send(device, sysex::yamaha_dx7::button_1(true));
        encode_and_send(device, sysex::yamaha_dx7::button_1(false));

        for (std::size_t _index = 0; _index < 3; ++_index) {
            encode_and_send(device, sysex::yamaha_dx7::button_8(true));
            encode_and_send(device, sysex::yamaha_dx7::button_8(false));
        }

        encode_and_send(device, sysex::yamaha_dx7::button_yes(true));
        encode_and_send(device, sysex::yamaha_dx7::button_yes(false));

        receive(_received);
        EXPECT_TRUE(sysex::decode(_received, device, _received_data));
        voice_1 = _received_data.bank_voices[0];
    }
};

TEST_F(yamaha_dx7_hardware, op_eg_rate_1)
{
    sysex::yamaha_dx7::device_id _device = 0;
    sysex::yamaha_dx7::op_id _op;
    sysex::yamaha_dx7::op_eg_rate_1 _op_eg_rate_1;
    sysex::yamaha_dx7::single_voice_bulk _voice_1_data;

    _op = sysex::yamaha_dx7::op_id::min_value;
    _op_eg_rate_1 = sysex::yamaha_dx7::op_eg_rate_1::min_value;
    encode_and_send(_device, _op, _op_eg_rate_1);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_1, _voice_1_data.ops_eg_rate_1[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::random(random_device);
    _op_eg_rate_1 = sysex::yamaha_dx7::op_eg_rate_1::random(random_device);
    encode_and_send(_device, _op, _op_eg_rate_1);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_1, _voice_1_data.ops_eg_rate_1[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::max_value;
    _op_eg_rate_1 = sysex::yamaha_dx7::op_eg_rate_1::max_value;
    encode_and_send(_device, _op, _op_eg_rate_1);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_1, _voice_1_data.ops_eg_rate_1[_op.value()]);
}

TEST_F(yamaha_dx7_hardware, op_eg_rate_2)
{
    sysex::yamaha_dx7::device_id _device = 0;
    sysex::yamaha_dx7::op_id _op;
    sysex::yamaha_dx7::op_eg_rate_2 _op_eg_rate_2;
    sysex::yamaha_dx7::single_voice_bulk _voice_1_data;

    _op = sysex::yamaha_dx7::op_id::min_value;
    _op_eg_rate_2 = sysex::yamaha_dx7::op_eg_rate_2::min_value;
    encode_and_send(_device, _op, _op_eg_rate_2);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_2, _voice_1_data.ops_eg_rate_2[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::random(random_device);
    _op_eg_rate_2 = sysex::yamaha_dx7::op_eg_rate_2::random(random_device);
    encode_and_send(_device, _op, _op_eg_rate_2);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_2, _voice_1_data.ops_eg_rate_2[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::max_value;
    _op_eg_rate_2 = sysex::yamaha_dx7::op_eg_rate_2::max_value;
    encode_and_send(_device, _op, _op_eg_rate_2);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_2, _voice_1_data.ops_eg_rate_2[_op.value()]);
}

TEST_F(yamaha_dx7_hardware, op_eg_rate_3)
{
    sysex::yamaha_dx7::device_id _device = 0;
    sysex::yamaha_dx7::op_id _op;
    sysex::yamaha_dx7::op_eg_rate_3 _op_eg_rate_3;
    sysex::yamaha_dx7::single_voice_bulk _voice_1_data;

    _op = sysex::yamaha_dx7::op_id::min_value;
    _op_eg_rate_3 = sysex::yamaha_dx7::op_eg_rate_3::min_value;
    encode_and_send(_device, _op, _op_eg_rate_3);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_3, _voice_1_data.ops_eg_rate_3[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::random(random_device);
    _op_eg_rate_3 = sysex::yamaha_dx7::op_eg_rate_3::random(random_device);
    encode_and_send(_device, _op, _op_eg_rate_3);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_3, _voice_1_data.ops_eg_rate_3[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::max_value;
    _op_eg_rate_3 = sysex::yamaha_dx7::op_eg_rate_3::max_value;
    encode_and_send(_device, _op, _op_eg_rate_3);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_3, _voice_1_data.ops_eg_rate_3[_op.value()]);
}

TEST_F(yamaha_dx7_hardware, op_eg_rate_4)
{
    sysex::yamaha_dx7::device_id _device = 0;
    sysex::yamaha_dx7::op_id _op;
    sysex::yamaha_dx7::op_eg_rate_4 _op_eg_rate_4;
    sysex::yamaha_dx7::single_voice_bulk _voice_1_data;

    _op = sysex::yamaha_dx7::op_id::min_value;
    _op_eg_rate_4 = sysex::yamaha_dx7::op_eg_rate_4::min_value;
    encode_and_send(_device, _op, _op_eg_rate_4);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_4, _voice_1_data.ops_eg_rate_4[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::random(random_device);
    _op_eg_rate_4 = sysex::yamaha_dx7::op_eg_rate_4::random(random_device);
    encode_and_send(_device, _op, _op_eg_rate_4);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_4, _voice_1_data.ops_eg_rate_4[_op.value()]);

    _op = sysex::yamaha_dx7::op_id::max_value;
    _op_eg_rate_4 = sysex::yamaha_dx7::op_eg_rate_4::max_value;
    encode_and_send(_device, _op, _op_eg_rate_4);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_op_eg_rate_4, _voice_1_data.ops_eg_rate_4[_op.value()]);
}

//
//
//
//
//
//
//
//
//
//
//
//

TEST_F(yamaha_dx7_hardware, algorithm_mode)
{
    sysex::yamaha_dx7::device_id _device = 0;
    sysex::yamaha_dx7::algorithm_mode _algorithm_mode;
    sysex::yamaha_dx7::single_voice_bulk _voice_1_data;

    _algorithm_mode = sysex::yamaha_dx7::algorithm_mode::min_value;
    encode_and_send(_device, _algorithm_mode);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_algorithm_mode, _voice_1_data.voice_algorithm_mode);

    _algorithm_mode = sysex::yamaha_dx7::algorithm_mode::random(random_device);
    encode_and_send(_device, _algorithm_mode);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_algorithm_mode, _voice_1_data.voice_algorithm_mode);

    _algorithm_mode = sysex::yamaha_dx7::algorithm_mode::max_value;
    encode_and_send(_device, _algorithm_mode);
    save_to_voice_1(_device);
    transmit_bank_read_voice_1(_device, _voice_1_data);
    EXPECT_EQ(_algorithm_mode, _voice_1_data.voice_algorithm_mode);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}