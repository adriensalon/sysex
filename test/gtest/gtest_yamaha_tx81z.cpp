#include <tuple>

#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_tx81z.hpp>

namespace midispec {
namespace yamaha_tx81z {

    struct yamaha_tx81z : public test_gtest {

        inline static std::mt19937 random_device;
    };

    namespace channel_common {

        TEST_F(yamaha_tx81z, note_off)
        {
            
        }

        TEST_F(yamaha_tx81z, note_on)
        {
            
        }

    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}