#include <tuple>

#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_spx90.hpp>

namespace midispec {
namespace yamaha_spx90 {

    struct yamaha_spx90 : public test_gtest {

        inline static std::mt19937 random_device;

        bool decode_note_off(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note)
        {
            if (encoded.size() != 3) {
                return false;
            }
            if ((encoded[0] & 0xF0) != 0x80) {
                return false;
            }

            channel = encoded[0] & 0x0F;
            note = encoded[1] & 0x7F;

            return true;
        }

        bool decode_note_on(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note)
        {
            if (encoded.size() != 3) {
                return false;
            }
            if ((encoded[0] & 0xF0) != 0x90) {
                return false;
            }

            channel = encoded[0] & 0x0F;
            note = encoded[1] & 0x7F;

            return true;
        }

        bool decode_program_change(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& program)
        {
            if (encoded.size() != 2) {
                return false;
            }
            if ((encoded[0] & 0xF0) != 0xC0) {
                return false;
            }

            channel = encoded[0] & 0x0F;
            program = encoded[1] & 0x7F;

            return true;
        }
    };

    namespace channel_common {

        TEST_F(yamaha_spx90, note_off)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _note;
            integral<std::uint8_t, 0, 127> _received_note;

            _note = _note.from_random(random_device);
            encode_note_off(_encoded, _channel, _note);
            EXPECT_TRUE(decode_note_off(_encoded, _received_channel, _received_note));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_note, _received_note);
        }

        TEST_F(yamaha_spx90, note_on)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _note;
            integral<std::uint8_t, 0, 127> _received_note;

            _note = _note.from_random(random_device);
            encode_note_on(_encoded, _channel, _note);
            EXPECT_TRUE(decode_note_on(_encoded, _received_channel, _received_note));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_note, _received_note);
        }

        TEST_F(yamaha_spx90, program_change)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _program;
            integral<std::uint8_t, 0, 127> _received_program;

            _program = _program.from_random(random_device);
            encode_program_change(_encoded, _channel, _program);
            EXPECT_TRUE(decode_program_change(_encoded, _received_channel, _received_program));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_program, _received_program);
        }

    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}