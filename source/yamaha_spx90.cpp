#include <midispec/yamaha_spx90.hpp>

/// User manual at
/// https://archive.org/details/SPX-90_owners_manual/page/n23/mode/2up

namespace midispec {
namespace yamaha_spx90 {
    namespace {
        // TODO
    }

    namespace channel_voice {

    }

    namespace system_exclusive {

        void encode_parameters_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            integral<std::uint8_t, 1, 4> bank_slot,
            integral<std::uint8_t, 1, 30> program_slot)
        {
        }

        void encode_program_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            integral<std::uint8_t, 1, 4> bank_slot,
            integral<std::uint8_t, 1, 30> program_slot)
        {
        }

        void encode_bank_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device)
        {
        }
    }
}
}