#include <midispec/yamaha_spx90.hpp>

/// User manual at
/// https://archive.org/details/SPX-90_owners_manual/page/n23/mode/2up

namespace midispec {
    
static_assert(has_note_off_v<yamaha_spx90, capability::receive>);
static_assert(has_note_on_v<yamaha_spx90, capability::receive>);
static_assert(has_program_change_v<yamaha_spx90, capability::receive>);

// channel common

void yamaha_spx90::encode_note_off(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x80 | (channel.value() & 0x0F));
    encoded.push_back(note.value());
    encoded.push_back(0x00);
}

void yamaha_spx90::encode_note_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x90 | (channel.value() & 0x0F));
    encoded.push_back(note.value());
    encoded.push_back(0x7F);
}

void yamaha_spx90::encode_program_change(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> program)
{
    encoded.push_back(0xC0 | (channel.value() & 0x0F));
    encoded.push_back(program.value());
}

// not tested
// system exclusive

namespace {
    static constexpr std::uint8_t SYSEX_START = 0xF0;
    static constexpr std::uint8_t SYSEX_END = 0xF7;
    static constexpr std::uint8_t SYSEX_YAMAHA = 0x43;

    static std::uint8_t compute_sysex_checksum(const std::uint8_t* p, std::size_t len)
    {
        std::uint32_t sum = 0;
        for (std::size_t i = 0; i < len; ++i) {
            sum += p[i];
        }
        return static_cast<std::uint8_t>((128 - (sum & 0x7F)) & 0x7F);
    }
}

void yamaha_spx90::encode_program_patch_bank_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 3> bank)
{
    encoded.push_back(SYSEX_START);
    encoded.push_back(SYSEX_YAMAHA);
    encoded.push_back(0x20 | (device.value() & 0x0F));
    encoded.push_back(0x7E);
    encoded.insert(encoded.end(), { 0x4C, 0x4D, 0x20, 0x20, 0x38, 0x33, 0x33, 0x32, 0x55 }); // LM  8332U
    encoded.push_back((bank.value() + 1) & 0x7F);
    encoded.push_back(SYSEX_END);
}

// bool decode_parameters(
//     const std::vector<std::uint8_t>& encoded,
//     integral<std::uint8_t, 0, 15>& device,
//     integral<std::uint8_t, 0, 89>& slot,
//     patch_parameters& data)
// {
//     if (encoded.size() < 4 || encoded.front() != 0xF0 || encoded.back() != 0xF7) {
//         std::cerr << "Invalid SysEx frame" << std::endl;
//         return false;
//     }

//     if (encoded[0] != SYSEX_START) {
//         std::cerr << "Invalid SysEx frame at index SYSEX_START" << std::endl;
//         return false;
//     }

//     if (encoded[1] != SYSEX_YAMAHA) {
//         std::cerr << "Invalid SysEx frame at index SYSEX_YAMAHA" << std::endl;
//         return false;
//     }

//     if ((encoded[2] & 0xF0) != 0x00) {
//         std::cerr << "Invalid SysEx frame at substatus index 2" << std::endl;
//         return false;
//     }

//     if (encoded[3] != 0x7E) {
//         std::cerr << "Invalid SysEx frame at index 3" << std::endl;
//         return false;
//     }

//     if (encoded[4] != 0x00) {
//         std::cerr << "Invalid SysEx frame at index 4" << std::endl;
//         return false;
//     }

//     if (encoded.size() < 15 || std::vector<std::uint8_t>(encoded.begin() + 5, encoded.begin() + 15) != std::vector<std::uint8_t>({ 0x4C, 0x4D, 0x20, 0x20, 0x38, 0x33, 0x33, 0x32, 0x54 })) {
//         std::cerr << "Invalid SysEx frame at indices 5-14" << std::endl;
//         return false;
//     }

//     if (encoded.size() < 15 + 1 + 78 + 1 + 1) {
//         std::cerr << "Invalid SysEx frame payload" << std::endl;
//         return false;
//     }

//     device = encoded[2] & 0x0F;
//     slot = (encoded[15] & 0x7F) - 1;
//     const uint8_t* _program_ptr = &encoded[16]; // 78 bytes

//     // NEED ACCESS TO REAL DATA TO IMPLEMENT

//     if ((encoded[94] & 0x7F) != compute_sysex_checksum(&encoded[4], (encoded.size() - 1 /*F7*/ - 1 /*CS*/) - 4)) {
//         std::cerr << "Invalid SysEx frame checksum" << std::endl;
//         return false;
//     }

//     return true;
// }

// bool decode_bank(
//     const std::vector<std::uint8_t>& encoded,
//     integral<std::uint8_t, 0, 15>& device,
//     integral<std::uint8_t, 0, 3>& bank,
//     std::array<patch, 30>& data)
// {
//     // NEED ACCESS TO REAL DATA TO IMPLEMENT
//     return true;
// }
}