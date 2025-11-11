#include <tuple>

#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_spx90.hpp>

namespace midispec {
namespace yamaha_spx90 {

    struct yamaha_spx90 : public hardware {

        inline static std::mt19937 random_device;
    };
    
    namespace channel_voice {

        TEST_F(yamaha_spx90, program_change)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 127> _data;
            
            _data = _data.from_random(random_device);
            encode_program_change(_encoded, _channel, _data);
            send(_encoded);
        }

        TEST_F(yamaha_spx90, note_off)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 127> _data;
            
            _data = _data.from_random(random_device);
            encode_note_off(_encoded, _channel, _data);
            send(_encoded);
        }

        TEST_F(yamaha_spx90, note_on)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 127> _data;
            
            _data = _data.from_random(random_device);
            encode_note_on(_encoded, _channel, _data);
            send(_encoded);
        }
    }

    namespace system_exclusive {

        TEST_F(yamaha_spx90, bank_request)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _device = 0;
            integral<std::uint8_t, 0, 3> _bank;
            
            _bank = _bank.from_random(random_device);
            encode_bank_request(_encoded, _device, _bank);
            send(_encoded);
        }

        TEST_F(yamaha_spx90, parameters)
        {
            std::vector<std::uint8_t> _encoded; // need real data
            integral<std::uint8_t, 0, 15> _device;
            integral<std::uint8_t, 0, 89> _slot;
            program_parameters _data = {};
            
            // decode_parameters(_encoded, _device, _slot, _data);
        }

        TEST_F(yamaha_spx90, bank)
        {
            std::vector<std::uint8_t> _encoded; // need real data
            integral<std::uint8_t, 0, 15> _device;
            integral<std::uint8_t, 0, 3> _bank;
            std::array<program, 30> _data = {};
            
            _bank = _bank.from_random(random_device);
            // decode_bank(_encoded, _device, _bank, _data);
        }

    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}