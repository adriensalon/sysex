#include <tuple>

#include <midispec/akai_lpk25.hpp>
#include <midispec/core/hardware.hpp>

namespace midispec {
namespace akai_lpk25 {

    struct akai_lpk25 : public test_gtest {

        inline static std::mt19937 random_device;
    };

    namespace channel_common {

        TEST_F(akai_lpk25, note_off)
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

        TEST_F(akai_lpk25, note_on)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _note;
            integral<std::uint8_t, 0, 127> _received_note;
            integral<std::uint8_t, 0, 127> _received_velocity;

            _note = _note.from_random(random_device);
            encode_note_on(_encoded, _channel, _note);
            EXPECT_TRUE(decode_note_on(_encoded, _received_channel, _received_note, _received_velocity));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_note, _received_note);
        }
    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}