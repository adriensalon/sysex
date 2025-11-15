#include <midispec/core/hardware.hpp>
#include <midispec/novation_launchpads.hpp>

namespace midispec {

struct gtest_novation_launchpads : public gtest_hardware {};

TEST_F(gtest_novation_launchpads, universal_inquiry)
{
    std::vector<std::uint8_t> _encoded;
    integral<std::uint8_t, 0, 127> _device = 0;
    integral<std::uint8_t, 0, 127> _received_device;
    std::uint32_t _received_manufacturer;
    std::uint32_t _received_family;
    std::uint32_t _received_model;
    std::uint32_t _received_version;

    novation_launchpads::encode_scrolling_text(_encoded, 44, 4, 0, "midispec is testing hardware...");
    novation_launchpads::encode_universal_inquiry_request(_encoded, _device);
    send(_encoded);
    EXPECT_TRUE(receive(_encoded));
    EXPECT_TRUE(novation_launchpads::decode_universal_inquiry(_encoded, _received_device, _received_manufacturer, _received_family, _received_model, _received_version));
    EXPECT_EQ(_device, _received_device);
    EXPECT_EQ(_received_manufacturer, 8233);
    EXPECT_EQ(_received_family, 32);
    EXPECT_EQ(_received_model, 0);
    // when tested version == 0
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}