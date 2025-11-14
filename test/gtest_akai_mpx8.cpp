#include <midispec/akai_mpx8.hpp>
#include <midispec/core/hardware.hpp>

namespace midispec {

struct gtest_akai_mpx8 : public gtest_hardware {};

TEST_F(gtest_akai_mpx8, universal_inquiry)
{
    std::vector<std::uint8_t> _encoded;
    integral<std::uint8_t, 0, 127> _device = 0;
    integral<std::uint8_t, 0, 127> _received_device;
    std::uint32_t _received_manufacturer;
    std::uint32_t _received_family;
    std::uint32_t _received_model;
    std::uint32_t _received_version;

    akai_mpx8::encode_universal_inquiry_request(_encoded, _device);
    send(_encoded);
    EXPECT_TRUE(receive(_encoded));
    EXPECT_TRUE(akai_mpx8::decode_universal_inquiry(_encoded, _received_device, _received_manufacturer, _received_family, _received_model, _received_version));
    // EXPECT_EQ(_received_manufacturer, "TODO");
    // EXPECT_EQ(_received_family, "TODO");
    // EXPECT_EQ(_received_model, "TODO");
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}