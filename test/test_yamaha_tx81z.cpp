#include <tuple>

#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_tx81z.hpp>

namespace midispec {
namespace yamaha_tx81z {

    struct yamaha_tx81z : public hardware {

        inline static std::mt19937 random_device;
    };

    namespace channel_voice {

        // TEST_F(yamaha_tx81z, note_off)
        // {
        //     std::vector<std::uint8_t> _encoded;
        //     integral<std::uint8_t, 0, 15> _channel = 0;
        //     integral<std::uint8_t, 0, 15> _received_channel;
        //     integral<std::uint8_t, 0, 127> _note;
        //     integral<std::uint8_t, 0, 127> _received_note;

        //     _note = _note.from_random(random_device);
        //     encode_note_off(_encoded, _channel, _note);
        //     decode_note_off(_encoded, _received_channel, _received_note);
        //     EXPECT_EQ(_channel, _received_channel);
        //     EXPECT_EQ(_note, _received_note);
        // }

        // TEST_F(yamaha_tx81z, note_on)
        // {
        //     std::vector<std::uint8_t> _encoded;
        //     integral<std::uint8_t, 0, 15> _channel = 0;
        //     integral<std::uint8_t, 0, 15> _received_channel;
        //     integral<std::uint8_t, 0, 127> _note;
        //     integral<std::uint8_t, 0, 127> _received_note;

        //     _note = _note.from_random(random_device);
        //     encode_note_on(_encoded, _channel, _note);
        //     decode_note_on(_encoded, _received_channel, _received_note);
        //     EXPECT_EQ(_channel, _received_channel);
        //     EXPECT_EQ(_note, _received_note);
        // }

        // TEST_F(yamaha_tx81z, program_change)
        // {
        //     std::vector<std::uint8_t> _encoded;
        //     integral<std::uint8_t, 0, 15> _channel = 0;
        //     integral<std::uint8_t, 0, 15> _received_channel;
        //     integral<std::uint8_t, 0, 127> _program;
        //     integral<std::uint8_t, 0, 127> _received_program;

        //     _program = _program.from_random(random_device);
        //     encode_program_change(_encoded, _channel, _program);
        //     decode_program_change(_encoded, _received_channel, _received_program);
        //     EXPECT_EQ(_channel, _received_channel);
        //     EXPECT_EQ(_program, _received_program);
        // }

    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}