#include <tuple>

#include <midispec/core/hardware.hpp>
#include <midispec/akai_mpx8.hpp>

namespace midispec {
namespace akai_mpx8 {

    struct akai_mpx8 : public test_gtest {

        inline static std::mt19937 random_device;
    };

    namespace channel_common {

        TEST_F(akai_mpx8, note_off)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _note;
            integral<std::uint8_t, 0, 127> _velocity;
            integral<std::uint8_t, 0, 127> _received_note;
            integral<std::uint8_t, 0, 127> _received_velocity;

            _note = _note.from_random(random_device);
            encode_note_off(_encoded, _channel, _note, _velocity);
            EXPECT_TRUE(decode_note_off(_encoded, _received_channel, _received_note, _received_velocity));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_note, _received_note);
            EXPECT_EQ(_velocity, _received_velocity);
        }

        TEST_F(akai_mpx8, note_on)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 15> _channel = 0;
            integral<std::uint8_t, 0, 15> _received_channel;
            integral<std::uint8_t, 0, 127> _note;
            integral<std::uint8_t, 0, 127> _velocity;
            integral<std::uint8_t, 0, 127> _received_note;
            integral<std::uint8_t, 0, 127> _received_velocity;

            _note = _note.from_random(random_device);
            _velocity = _velocity.from_random(random_device);
            encode_note_on(_encoded, _channel, _note, _velocity);
            EXPECT_TRUE(decode_note_on(_encoded, _received_channel, _received_note, _received_velocity));
            EXPECT_EQ(_channel, _received_channel);
            EXPECT_EQ(_note, _received_note);
            EXPECT_EQ(_velocity, _received_velocity);
        }
    }

    namespace system_exclusive {

        TEST_F(akai_mpx8, universal_inquiry)
        {
            std::vector<std::uint8_t> _encoded;
            integral<std::uint8_t, 0, 127> _device = 0;
            integral<std::uint8_t, 0, 127> _received_device;
            std::uint32_t _received_manufacturer;
            std::uint32_t _received_family;
            std::uint32_t _received_model;
            std::uint32_t _received_version;

            encode_universal_inquiry_request(_encoded, _device);
            send(_encoded);
            EXPECT_TRUE(receive(_encoded));
            EXPECT_TRUE(decode_universal_inquiry(_encoded, _received_device, _received_manufacturer, _received_family, _received_model, _received_version));
            // EXPECT_EQ(_received_manufacturer, "TODO");
            // EXPECT_EQ(_received_family, "TODO");
            // EXPECT_EQ(_received_model, "TODO");
        }

    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}