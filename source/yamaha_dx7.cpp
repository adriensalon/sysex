#include <algorithm>
#include <cassert>

#include <sysex/yamaha_dx7.hpp>

namespace sysex {
namespace {

    struct vmem_header {
        yamaha_dx7::device_id device;
        std::uint8_t group;
        std::uint8_t length_hi;
        std::uint8_t length_lo;
        std::size_t payload_offset;
        std::size_t payload_length;
    };

    static constexpr std::uint8_t SYSEX_START = 0xF0;
    static constexpr std::uint8_t SYSEX_END = 0xF7;
    static constexpr std::uint8_t SYSEX_YAMAHA_ID = 0x43;

    static constexpr std::uint8_t SYSEX_GROUP_VOICE = 0;
    static constexpr std::uint8_t SYSEX_GROUP_GLOBAL = 2;

    static constexpr std::uint8_t SYSEX_VOICE_OP_BLOCK_STRIDE = 21;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_RATE_1 = 0;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_RATE_2 = 1;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_RATE_3 = 2;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_RATE_4 = 3;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_LEVEL_1 = 4;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_LEVEL_2 = 5;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_LEVEL_3 = 6;
    static constexpr std::uint8_t SYSEX_VOICE_OP_EG_LEVEL_4 = 7;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_BREAKPOINT = 8;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_LEFT_DEPTH = 9;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_RIGHT_DEPTH = 10;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_LEFT_CURVE = 11;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_RIGHT_CURVE = 12;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING = 13;
    static constexpr std::uint8_t SYSEX_VOICE_OP_AMPLITUDE_MODULATION_SENSITIVITY = 14;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEY_VELOCITY_SENSITIVITY = 15;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OUTPUT_LEVEL = 16;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OSCILLATOR_MODE = 17;
    static constexpr std::uint8_t SYSEX_VOICE_OP_COARSE = 18;
    static constexpr std::uint8_t SYSEX_VOICE_OP_FINE = 19;
    static constexpr std::uint8_t SYSEX_VOICE_OP_DETUNE = 20;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_RATE_1 = 125;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_RATE_2 = 126;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_RATE_3 = 127;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_RATE_4 = 128;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_LEVEL_1 = 130;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_LEVEL_2 = 131;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_LEVEL_3 = 132;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENV_LEVEL_4 = 133;
    static constexpr std::uint8_t SYSEX_VOICE_ALGORITHM_MODE = 134;
    static constexpr std::uint8_t SYSEX_VOICE_FEEDBACK = 135;
    static constexpr std::uint8_t SYSEX_VOICE_OSC_KEY_SYNC = 136;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_SPEED = 137;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_DELAY = 138;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_PMD = 139;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_AMD = 140;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_SYNC = 141;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_WAVE = 142;
    static constexpr std::uint8_t SYSEX_VOICE_PMS = 143;
    static constexpr std::uint8_t SYSEX_VOICE_TRANSPOSE = 144;
    static constexpr std::uint8_t SYSEX_VOICE_VOICE_NAME_1 = 145; // ASCII, 7-bit
    static constexpr std::uint8_t SYSEX_VOICE_VOICE_NAME_10 = 154; // inclusive
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENABLE_MASK = 155; // bit5=OP1 … bit0=OP6 (only via param-change; not in bulk)

    static constexpr std::uint8_t SYSEX_GLOBAL_MONO_POLY = 64; // 0=poly,1=mono
    static constexpr std::uint8_t SYSEX_GLOBAL_PB_RANGE = 65; // 0..12
    static constexpr std::uint8_t SYSEX_GLOBAL_PB_STEP = 66; // 0..12
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_MODE = 67; // 0=retain,1=follow
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_GLISSANDO = 68; // 0/1
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_TIME = 69; // 0..99
    static constexpr std::uint8_t SYSEX_GLOBAL_MOD_RANGE = 70; // 0..99
    static constexpr std::uint8_t SYSEX_GLOBAL_MOD_ASSIGN = 71; // bit0: pitch, bit1: amp, bit2: EG bias
    static constexpr std::uint8_t SYSEX_GLOBAL_FOOT_RANGE = 72; // 0..99
    static constexpr std::uint8_t SYSEX_GLOBAL_FOOT_ASSIGN = 73;
    static constexpr std::uint8_t SYSEX_GLOBAL_BREATH_RANGE = 74; // 0..99
    static constexpr std::uint8_t SYSEX_GLOBAL_BREATH_ASSIGN = 75;
    static constexpr std::uint8_t SYSEX_GLOBAL_AT_RANGE = 76; // 0..99
    static constexpr std::uint8_t SYSEX_GLOBAL_AT_ASSIGN = 77;

    static constexpr std::uint8_t SYSEX_BUTTON_1 = 0x00;
    static constexpr std::uint8_t SYSEX_BUTTON_2 = 0x01;
    static constexpr std::uint8_t SYSEX_BUTTON_3 = 0x02;
    static constexpr std::uint8_t SYSEX_BUTTON_4 = 0x03;
    static constexpr std::uint8_t SYSEX_BUTTON_5 = 0x04;
    static constexpr std::uint8_t SYSEX_BUTTON_6 = 0x05;
    static constexpr std::uint8_t SYSEX_BUTTON_7 = 0x06;
    static constexpr std::uint8_t SYSEX_BUTTON_8 = 0x07;
    static constexpr std::uint8_t SYSEX_BUTTON_STORE = 0x20;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_PROTECT_INTERNAL = 0x21;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_PROTECT_CARTRIDGE = 0x22;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_SELECT_INTERNAL = 0x25;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_SELECT_CARTRIDGE = 0x26;
    static constexpr std::uint8_t SYSEX_BUTTON_FUNCTION = 0x27;
    static constexpr std::uint8_t SYSEX_BUTTON_NO = 0x28;
    static constexpr std::uint8_t SYSEX_BUTTON_YES = 0x29;

    static constexpr std::uint8_t SYSEX_VMEM_BANK = 0x09;
    static constexpr std::uint8_t SYSEX_VMEM_LEN_HI = 0x20;
    static constexpr std::uint8_t SYSEX_VMEM_LEN_LO = 0x00;

    static std::uint8_t checksum7(const std::uint8_t* data, const std::size_t length)
    {
        std::uint32_t _sum = 0;
        for (std::size_t _index = 0; _index < length; ++_index) {
            _sum += (data[_index] & 0x7F);
        }
        return (128 - (_sum & 0x7F)) & 0x7F;
    }

    static void append_param_change(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const std::uint8_t group, const std::uint16_t parameter, const std::uint8_t value)
    {
        // Split param_number across the “group/param-hi” and the “param-lo” bytes.
        // The DX7 packs the high bit(s) of the parameter number into the low two
        // bits of the “group” byte (that spec’s 0ggggpp). In practice for DX7 voice
        // params you only need one extra bit (for 128..155).
        const std::uint8_t _parameter_high = (parameter >> 7) & 0x01;
        const std::uint8_t _parameter_low = parameter & 0x7F;
        const std::uint8_t _group_and_high = ((group & 0x1F) << 2) | (_parameter_high & 0x03);

        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA_ID);
        encoded.push_back(0x10 | (device.value() & 0x0F));
        encoded.push_back(_group_and_high);
        encoded.push_back(_parameter_low);
        encoded.push_back(value & 0x7F);
        encoded.push_back(SYSEX_END);
    }

    static void append_button(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const std::uint8_t button, const bool press)
    {
        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA_ID);
        encoded.push_back(0x10 | (device.value() & 0x0F));
        encoded.push_back(0x08);
        encoded.push_back(button & 0x7F);
        encoded.push_back(press ? 0x7F : 0x00);
        encoded.push_back(SYSEX_END);
    }

    static void append_bulk_header(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const std::uint8_t group, const std::uint8_t length_hi, const std::uint8_t length_lo)
    {
        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA_ID);
        encoded.push_back(0x00 | (device.value() & 0x0F));
        encoded.push_back(group & 0x7F);
        encoded.push_back(length_hi & 0x7F);
        encoded.push_back(length_lo & 0x7F);
    }

    static void append_bulk_finish(std::vector<std::uint8_t>& encoded, const std::uint8_t* payload, const std::size_t payload_length)
    {
        encoded.insert(encoded.end(), payload, payload + payload_length);
        encoded.push_back(checksum7(payload, payload_length) & 0x7F);
        encoded.push_back(SYSEX_END);
    }

    static bool parse_bulk_header(const std::vector<std::uint8_t>& encoded, vmem_header& header)
    {
        if (encoded.size() < 8 || encoded[0] != SYSEX_START || encoded[1] != SYSEX_YAMAHA_ID || encoded.back() != SYSEX_END) {
            std::cerr << "Invalid source encoded data" << std::endl;
            return false;
        }

        const bool _vmem_byte_is_correct = (encoded[2] & 0x70) == 0x00;
        if (!_vmem_byte_is_correct) {
            std::cerr << "Invalid vmem byte" << std::endl;
            return false;
        }

        header.group = encoded[3] & 0x7F;
        header.length_hi = encoded[4] & 0x7F;
        header.length_lo = encoded[5] & 0x7F;
        header.payload_offset = 6;
        header.payload_length = encoded.size() - 6 /*hdr*/ - 1 /*cs*/ - 1 /*F7*/;
        if (header.payload_length == 0) {
            std::cerr << "Invalid payload length" << std::endl;
            return false;
        }

        const std::size_t _checksum_index = encoded.size() - 2;
        const std::uint8_t _checksum_calculation = checksum7(encoded.data() + header.payload_offset, header.payload_length);
        if ((encoded[_checksum_index] & 0x7F) != _checksum_calculation) {
            std::cerr << "Invalid checksum calculation" << std::endl;
            return false;
        }

        return true;
    }
}

// encode

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_1& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_RATE_1, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_2& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_RATE_2, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_3& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_RATE_3, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_rate_4& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_RATE_4, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_1& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_LEVEL_1, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_2& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_LEVEL_2, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_3& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_LEVEL_3, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::op_id op, const yamaha_dx7::op_eg_level_4& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, static_cast<std::uint8_t>((5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE) + SYSEX_VOICE_OP_EG_LEVEL_4, data.value());
}

// void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const std::uint8_t op, const yamaha_dx7::op_keyboard_scaling& data)
// {
//     const std::uint8_t _op_base = static_cast<std::uint8_t>((5 - op.value()) * SYSEX_OP_BLOCK_STRIDE);
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_BP, clamp7(data.break_point, 0, 99));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_LEFT_DEPTH, clamp7(data.left_depth, 0, 99));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_RIGHT_DEPTH, clamp7(data.right_depth, 0, 99));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_LEFT_CURVE, static_cast<std::uint8_t>(data.left_curve));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_RIGHT_CURVE, static_cast<std::uint8_t>(data.right_curve));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEYBOARD_SCALING, clamp7(data.rate_scaling, 0, 7));
// }

// void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const std::uint8_t op, const yamaha_dx7::op_velocity_amp& data)
// {
//     const std::uint8_t _op_base = static_cast<std::uint8_t>((5 - op.value()) * SYSEX_OP_BLOCK_STRIDE);
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_KEY_VELOCITY_SENSITIVITY, clamp7(data.velocity_sensitivity, 0, 7));
//     append_param_change(encoded, device, SYSEX_GROUP_VOICE, _op_base + SYSEX_OP_AMPLITUDE_MODULATION_SENSITIVITY, clamp7(data.amp_mod_sensitivity, 0, 3));
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const std::uint8_t op, const yamaha_dx7::op_output_level& d)
// {
//     const std::uint16_t a = addr::OP_OUTPUT_LEVEL_BASE /* + stride*(d.op-1) */;
//     const std::uint8_t v = clamp7(d.level, 0, 99);
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const std::uint8_t op, const yamaha_dx7::op_oscillator& d)
// {
//     const std::uint16_t a = addr::OP_OSC_BASE /* + stride*(d.op-1) */;
//     // Typical packing is separate bytes; if the DX7 packs bits, adjust here.
//     std::uint8_t payload[4] = {
//         static_cast<std::uint8_t>(d.mode),
//         clamp7(d.coarse, 0, 31),
//         clamp7(d.fine, 0, 99),
//         encode_detune(d.detune)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::pitch_envelope_rates& d)
// {
//     const std::uint16_t a = addr::PITCH_ENV_RATES;
//     std::uint8_t payload[4] = {
//         clamp7(d.rate_1, 0, 99), clamp7(d.rate_2, 0, 99),
//         clamp7(d.rate_3, 0, 99), clamp7(d.rate_4, 0, 99)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::pitch_envelope_levels& d)
// {
//     const std::uint16_t a = addr::PITCH_ENV_LEVELS;
//     std::uint8_t payload[4] = {
//         clamp7(d.level_1, 0, 99), clamp7(d.level_2, 0, 99),
//         clamp7(d.level_3, 0, 99), clamp7(d.level_4, 0, 99)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::algorithm_mode& data)
{
    append_param_change(encoded, device, SYSEX_GROUP_VOICE, SYSEX_VOICE_ALGORITHM_MODE, data.value());
}

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::algorithm_feedback& d)
// {
//     const std::uint16_t a = addr::ALGO_FEEDBACK;
//     std::uint8_t payload[2] = {
//         static_cast<std::uint8_t>(d.algorithm), // 1..32 stored 1..32 or 0..31 depending on spec
//         clamp7(d.feedback, 0, 7)
//     };
//     append_param_change(out, dev, a, payload, 2);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::oscillator_key_sync& d)
// {
//     const std::uint16_t a = addr::OSC_KEY_SYNC;
//     const std::uint8_t v = d.enable ? 1 : 0;
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::lfo_settings& d)
// {
//     const std::uint16_t a = addr::LFO_SETTINGS;
//     std::uint8_t payload[6] = {
//         static_cast<std::uint8_t>(d.waveform),
//         clamp7(d.speed, 0, 99),
//         clamp7(d.delay, 0, 99),
//         clamp7(d.pitch_mod_depth, 0, 99),
//         clamp7(d.amp_mod_depth, 0, 99),
//         static_cast<std::uint8_t>(d.sync ? 1 : 0)
//     };
//     append_param_change(out, dev, a, payload, 6);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::pitch_modulation_sensitivity& d)
// {
//     const std::uint16_t a = addr::PMS;
//     const std::uint8_t v = clamp7(d.sensitivity, 0, 7);
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::transpose& d)
// {
//     const std::uint16_t a = addr::TRANSPOSE;
//     // DX7 typically encodes transpose as 0..48 with 24 = 0 semis; adjust if needed.
//     const std::int8_t st = clamp<std::int8_t>(d.semitones, -24, 24);
//     const std::uint8_t v = static_cast<std::uint8_t>(st + 24);
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::op_enable_mask& d)
// {
//     const std::uint16_t a = addr::OP_ENABLE_MASK;
//     const std::uint8_t v = d.mask & 0x3F;
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::voice_name& d)
// {
//     const std::uint16_t a = addr::VOICE_NAME_BASE;
//     // 10 bytes; ensure 7-bit clean ASCII (DX7 ignores high bit).
//     std::uint8_t payload[10];
//     for (int i = 0; i < 10; ++i) {
//         char c = d.name[i];
//         if (c == '\0')
//             c = ' ';
//         payload[i] = static_cast<std::uint8_t>(c) & 0x7F;
//     }
//     append_param_change(out, dev, a, payload, 10);
// }

// // Bulk single-voice encode (optional, if you later add a raw VCED image)
// // Your current patch type is structured, so we don’t have the 155-byte blob.
// // Keep this as a forwarding orchestration if you want to send a whole patch
// // as individual param-change messages.
// void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::single_voice_bulk& data)
// {
//     std::array<std::uint8_t, 155> vced {};
//     pack_vced_from_struct(data, vced);

//     append_bulk_header(encoded, device, GROUP_VCED_SINGLE, VCED_LEN_HI, VCED_LEN_LO);
//     append_bulk_finish(encoded, vced.data(), vced.size());
// }

// void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::bank_bulk& data)
// {
//     std::vector<std::uint8_t> vmem;
//     pack_vmem_from_struct(data, vmem);

//     append_bulk_header(encoded, device, GROUP_VMEM_BANK, VMEM_LEN_HI, VMEM_LEN_LO);
//     append_bulk_finish(encoded, vmem.data(), vmem.size());
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::pitch_bend& d)
// {
//     // TODO: fill with the real address/packing if you want to set via param-change
//     const std::uint16_t a = addr::PITCH_BEND_GLOBAL;
//     std::uint8_t payload[3] = {
//         clamp7(d.up_semitones, 0, 12),
//         clamp7(d.down_semitones, 0, 12),
//         clamp7(d.step, 0, 12)
//     };
//     append_param_change(out, dev, a, payload, 3);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::portamento& d)
// {
//     const std::uint16_t a = addr::PORTAMENTO_GLOBAL;
//     std::uint8_t payload[4] = {
//         static_cast<std::uint8_t>(d.enabled ? 1 : 0),
//         clamp7(d.time, 0, 99),
//         static_cast<std::uint8_t>(d.fingered ? 1 : 0),
//         static_cast<std::uint8_t>(d.glissando ? 1 : 0),
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::mono_poly& d)
// {
//     const std::uint16_t a = addr::MONO_POLY_GLOBAL;
//     std::uint8_t payload[3] = {
//         static_cast<std::uint8_t>(d.mono ? 1 : 0),
//         static_cast<std::uint8_t>(d.unison ? 1 : 0),
//         clamp7(d.unison_detune, 0, 7)
//     };
//     append_param_change(out, dev, a, payload, 3);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::aftertouch& d)
// {
//     const std::uint16_t a = addr::AFTERTOUCH_GLOBAL;
//     const std::uint8_t v = d.enable ? 1 : 0;
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::foot_controller& d)
// {
//     const std::uint16_t a = addr::FOOT_CTRL_GLOBAL;
//     std::uint8_t payload[4] = {
//         static_cast<std::uint8_t>(d.to_pitch ? 1 : 0),
//         static_cast<std::uint8_t>(d.to_amp ? 1 : 0),
//         static_cast<std::uint8_t>(d.to_bias ? 1 : 0),
//         clamp7(d.depth, 0, 99)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::breath_controller& d)
// {
//     const std::uint16_t a = addr::BREATH_CTRL_GLOBAL;
//     std::uint8_t payload[4] = {
//         static_cast<std::uint8_t>(d.to_pitch ? 1 : 0),
//         static_cast<std::uint8_t>(d.to_amp ? 1 : 0),
//         static_cast<std::uint8_t>(d.to_bias ? 1 : 0),
//         clamp7(d.depth, 0, 99)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::mod_wheel& data)
// {
//     const std::uint16_t a = addr::MOD_WHEEL_GLOBAL;
//     std::uint8_t payload[4] = {
//         static_cast<std::uint8_t>(data.to_pitch ? 1 : 0),
//         static_cast<std::uint8_t>(data.to_amp ? 1 : 0),
//         static_cast<std::uint8_t>(data.to_bias ? 1 : 0),
//         clamp7(data.depth, 0, 99)
//     };
//     append_param_change(out, dev, a, payload, 4);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::master_tune& data)
// {
//     const std::uint16_t a = addr::MASTER_TUNE;
//     // Map ±100 cents to e.g. 0..200 with 100 = center if that’s what DX7 expects.
//     const std::int16_t cents = clamp<std::int16_t>(data.cents, -100, 100);
//     const std::uint8_t v = static_cast<std::uint8_t>(cents + 100);
//     append_param_change(out, dev, a, &v, 1);
// }

// void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::function_block& data)
// {
//     std::array<std::uint8_t, 52> func {};
//     pack_function_from_struct(data, func);

//     append_bulk_header(encoded, device, GROUP_FUNCTION, FUNC_LEN_HI, FUNC_LEN_LO);
//     append_bulk_finish(encoded, func.data(), func.size());
// }

// // Memory Protect (Mk I): implemented using remote panel buttons
// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::memory_protect_internal& data)
// {
//     // Press/release “MEM PROTECT INTERNAL”, then YES/NO press/release
//     append_button(out, dev, SYSEX_BUTTON_MEMORY_PROTECT_INTERNAL, true);
//     append_button(out, dev, SYSEX_BUTTON_MEMORY_PROTECT_INTERNAL, false);
//     append_button(out, dev, data.enable ? BTN_YES : BTN_NO, true);
//     append_button(out, dev, data.enable ? BTN_YES : BTN_NO, false);
// }

// void encode(std::vector<std::uint8_t>& out, const yamaha_dx7::device_id dev, const yamaha_dx7::memory_protect_cartridge& data)
// {
//     append_button(out, dev, BTN_MEMPROT_CART, true);
//     append_button(out, dev, BTN_MEMPROT_CART, false);
//     append_button(out, dev, data.enable ? BTN_YES : BTN_NO, true);
//     append_button(out, dev, data.enable ? BTN_YES : BTN_NO, false);
// }

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_1& data)
{
    append_button(encoded, device, SYSEX_BUTTON_1, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_2& data)
{
    append_button(encoded, device, SYSEX_BUTTON_2, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_8& data)
{
    append_button(encoded, device, SYSEX_BUTTON_8, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_store& data)
{
    append_button(encoded, device, SYSEX_BUTTON_STORE, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_protect_internal& data)
{
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_protect_cartridge& data)
{
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_select_internal& data)
{
    append_button(encoded, device, SYSEX_BUTTON_MEMORY_SELECT_INTERNAL, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_memory_select_cartridge& data)
{
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_function& data)
{
    append_button(encoded, device, SYSEX_BUTTON_FUNCTION, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_no& data)
{
    append_button(encoded, device, SYSEX_BUTTON_NO, data.value());
}

void encode(std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, const yamaha_dx7::button_yes& data)
{
    append_button(encoded, device, SYSEX_BUTTON_YES, data.value());
}

// decode

bool decode(const std::vector<std::uint8_t>& encoded, const yamaha_dx7::device_id device, yamaha_dx7::bank_bulk& data)
{
    vmem_header _header;

    if (!parse_bulk_header(encoded, _header)) {
        std::cerr << "Failed to parse Yamaha DX7 bulk header from transmitted data" << std::endl;
        return false;
    }

    if (_header.group != SYSEX_VMEM_BANK || _header.length_hi != SYSEX_VMEM_LEN_HI || _header.length_lo != SYSEX_VMEM_LEN_LO) {
        std::cerr << "Failed to parse Yamaha DX7 bulk header because of incorrect constants" << std::endl;
        return false;
    }

    if (_header.payload_length != 4096) {
        std::cerr << "Failed to parse Yamaha DX7 bulk header because of incorrect payload length" << std::endl;
        return false;
    }

    const std::uint8_t* _payload = encoded.data() + _header.payload_offset;
    for (std::size_t _voice_index = 0; _voice_index < 32; ++_voice_index) {

        const std::uint8_t* _vmem_ptr = _payload + _voice_index * 128;
        for (std::size_t _op_reversed_index = 0; _op_reversed_index < 6; ++_op_reversed_index) {

            const std::size_t _op_base = _op_reversed_index * 17; // 0,17,34,51,68,85
            const std::size_t _op_index = 5 - _op_reversed_index; // map to OP index 0..5  (0=OP1 ... 5=OP6)

            data.bank_voices[_voice_index].ops_eg_rate_1[_op_index] = _vmem_ptr[_op_base + 0];
            data.bank_voices[_voice_index].ops_eg_rate_2[_op_index] = _vmem_ptr[_op_base + 1];
            data.bank_voices[_voice_index].ops_eg_rate_3[_op_index] = _vmem_ptr[_op_base + 2];
            data.bank_voices[_voice_index].ops_eg_rate_4[_op_index] = _vmem_ptr[_op_base + 3];

            data.bank_voices[_voice_index].ops_eg_level_1[_op_index] = _vmem_ptr[_op_base + 4];
            data.bank_voices[_voice_index].ops_eg_level_2[_op_index] = _vmem_ptr[_op_base + 5];
            data.bank_voices[_voice_index].ops_eg_level_3[_op_index] = _vmem_ptr[_op_base + 6];
            data.bank_voices[_voice_index].ops_eg_level_4[_op_index] = _vmem_ptr[_op_base + 7];

            // data.bank_voices[i].ops_keyboard_scaling_breakpoint[op] = v[base + 8];
            // data.bank_voices[i].ops_keyboard_scaling_left_depth[op] = v[base + 9];
            // data.bank_voices[i].ops_keyboard_scaling_right_depth[op] = v[base + 10];

            // data.bank_voices[i].ops_keyboard_scaling_left_curve[op] = static_cast<sysex::yamaha_dx7::curve>(v[base + 11] & 0x03);
            // data.bank_voices[i].ops_keyboard_scaling_right_curve[op] = static_cast<sysex::yamaha_dx7::curve>(v[base + 12] & 0x03);

            // data.bank_voices[i].ops_keyboard_scaling_rate[op] = v[base + 13] & 0x07;
            // data.bank_voices[i].ops_amplitude_modulation_sensitivity[op] = v[base + 14] & 0x03;
            // data.bank_voices[i].ops_velocity_sensitivity[op] = v[base + 15] & 0x07;
            // data.bank_voices[i].ops_output_level[op] = v[base + 16];
        }

        // data.bank_voices[i].voice_pitch_envelope_rate_1 = v[102];
        // data.bank_voices[i].voice_pitch_envelope_rate_2 = v[103];
        // data.bank_voices[i].voice_pitch_envelope_rate_3 = v[104];
        // data.bank_voices[i].voice_pitch_envelope_rate_4 = v[105];

        // data.bank_voices[i].voice_pitch_envelope_level_1 = v[106];
        // data.bank_voices[i].voice_pitch_envelope_level_2 = v[107];
        // data.bank_voices[i].voice_pitch_envelope_level_3 = v[108];
        // data.bank_voices[i].voice_pitch_envelope_level_4 = v[109];

        data.bank_voices[_voice_index].voice_algorithm_mode = _vmem_ptr[110] & 0x7F;
    }
    return true;
}

}
