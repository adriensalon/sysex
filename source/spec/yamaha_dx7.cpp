#include <midispec/spec/yamaha_dx7.hpp>

/// User manual at
/// https://synthfool.com/docs/Yamaha/DX_Series/Yamaha%20DX7%20Operating%20Manual.pdf

namespace midispec {

namespace {
    static constexpr std::uint8_t SYSEX_START = 0xF0;
    static constexpr std::uint8_t SYSEX_END = 0xF7;
    static constexpr std::uint8_t SYSEX_YAMAHA = 0x43;

    static constexpr std::uint8_t SYSEX_GROUP_VOICE = 0;
    static constexpr std::uint8_t SYSEX_GROUP_FUNCTION = 2;

    static constexpr std::uint8_t SYSEX_VOICE_OP_BLOCK_STRIDE = 21;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_1 = 0;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_2 = 1;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_3 = 2;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_4 = 3;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_1 = 4;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_2 = 5;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_3 = 6;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_4 = 7;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_BREAKPOINT = 8;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_DEPTH = 9;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_DEPTH = 10;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_CURVE = 11;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_CURVE = 12;
    static constexpr std::uint8_t SYSEX_VOICE_OP_KEYBOARD_SCALING_RATE = 13;
    static constexpr std::uint8_t SYSEX_VOICE_OP_AMPLITUDE_MODULATION_SENSITIVITY = 14;
    static constexpr std::uint8_t SYSEX_VOICE_OP_VELOCITY_SENSITIVITY = 15;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OUTPUT_LEVEL = 16;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OSCILLATOR_MODE = 17;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OSCILLATOR_COARSE = 18;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OSCILLATOR_FINE = 19;
    static constexpr std::uint8_t SYSEX_VOICE_OP_OSCILLATOR_DETUNE = 20;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_RATE_1 = 126;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_RATE_2 = 127;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_RATE_3 = 128;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_RATE_4 = 129;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_1 = 130;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_2 = 131;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_3 = 132;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_4 = 133;
    static constexpr std::uint8_t SYSEX_VOICE_ALGORITHM_MODE = 134;
    static constexpr std::uint8_t SYSEX_VOICE_ALGORITHM_FEEDBACK = 135;
    static constexpr std::uint8_t SYSEX_VOICE_OSCILLATOR_KEY_SYNC = 136;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_SPEED = 137;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_DELAY = 138;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_PITCH_MODULATION_DEPTH = 139;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_AMPLITUDE_MODULATION_DEPTH = 140;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_SYNC = 141;
    static constexpr std::uint8_t SYSEX_VOICE_LFO_WAVEFORM = 142;
    static constexpr std::uint8_t SYSEX_VOICE_PITCH_MODULATION_SENSITIVITY = 143;
    static constexpr std::uint8_t SYSEX_VOICE_TRANSPOSE = 144;
    static constexpr std::uint8_t SYSEX_VOICE_VOICE_NAME_1 = 145;
    static constexpr std::uint8_t SYSEX_VOICE_VOICE_NAME_10 = 154;
    static constexpr std::uint8_t SYSEX_VOICE_OP_ENABLE_MASK = 155;

    static constexpr std::uint8_t SYSEX_GLOBAL_MONO_POLY_MODE = 64;
    static constexpr std::uint8_t SYSEX_GLOBAL_pitchbend_RANGE = 65;
    static constexpr std::uint8_t SYSEX_GLOBAL_pitchbend_STEP = 66;
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_MODE = 67;
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_GLISSANDO = 68;
    static constexpr std::uint8_t SYSEX_GLOBAL_PORTAMENTO_TIME = 69;
    static constexpr std::uint8_t SYSEX_GLOBAL_MODULATION_WHEEL_RANGE = 70;
    static constexpr std::uint8_t SYSEX_GLOBAL_MODULATION_WHEEL_ASSIGN = 71;
    static constexpr std::uint8_t SYSEX_GLOBAL_FOOT_CONTROLLER_RANGE = 72;
    static constexpr std::uint8_t SYSEX_GLOBAL_FOOT_CONTROLLER_ASSIGN = 73;
    static constexpr std::uint8_t SYSEX_GLOBAL_BREATH_CONTROLLER_RANGE = 74;
    static constexpr std::uint8_t SYSEX_GLOBAL_BREATH_CONTROLLER_ASSIGN = 75;
    static constexpr std::uint8_t SYSEX_GLOBAL_AFTER_TOUCH_RANGE = 76;
    static constexpr std::uint8_t SYSEX_GLOBAL_AFTER_TOUCH_ASSIGN = 77;

    static constexpr std::uint8_t SYSEX_BUTTON_1 = 0x00;
    static constexpr std::uint8_t SYSEX_BUTTON_STORE = 0x20;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_PROTECT_INTERNAL = 0x21;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_PROTECT_CARTRIDGE = 0x22;
    static constexpr std::uint8_t SYSEX_BUTTON_OPERATOR_SELECT = 0x23;
    static constexpr std::uint8_t SYSEX_BUTTON_EDIT_COMPARE = 0x24;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_SELECT_INTERNAL = 0x25;
    static constexpr std::uint8_t SYSEX_BUTTON_MEMORY_SELECT_CARTRIDGE = 0x26;
    static constexpr std::uint8_t SYSEX_BUTTON_FUNCTION = 0x27;
    static constexpr std::uint8_t SYSEX_BUTTON_NO = 0x28;
    static constexpr std::uint8_t SYSEX_BUTTON_YES = 0x29;

    static constexpr std::uint8_t SYSEX_VCED_SINGLE = 0x00;
    static constexpr std::uint8_t SYSEX_VCED_LENGTH_HIGH = 0x01;
    static constexpr std::uint8_t SYSEX_VCED_LENGTH_LOW = 0x1B;

    static constexpr std::uint8_t SYSEX_VMEM_BANK = 0x09;
    static constexpr std::uint8_t SYSEX_VMEM_LENGTH_HIGH = 0x20;
    static constexpr std::uint8_t SYSEX_VMEM_LENGTH_LOW = 0x00;

    static std::uint8_t compute_sysex_checksum(const std::uint8_t* data, const std::size_t length)
    {
        std::uint32_t _sum = 0;
        for (std::size_t _index = 0; _index < length; ++_index) {
            _sum += (data[_index] & 0x7F);
        }
        return (128 - (_sum & 0x7F)) & 0x7F;
    }

    static void encode_sysex_parameter(std::vector<std::uint8_t>& encoded, const std::uint8_t device, const std::uint8_t group, const std::uint16_t parameter, const std::uint8_t value)
    {
        const std::uint8_t _parameter_high = (parameter >> 7) & 0x01;
        const std::uint8_t _parameter_low = parameter & 0x7F;
        const std::uint8_t _group_and_high = ((group & 0x1F) << 2) | (_parameter_high & 0x03);

        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA);
        encoded.push_back(0x10 | (device & 0x0F));
        encoded.push_back(_group_and_high);
        encoded.push_back(_parameter_low);
        encoded.push_back(value & 0x7F);
        encoded.push_back(SYSEX_END);
    }

    static void encode_sysex_button(std::vector<std::uint8_t>& encoded, const std::uint8_t device, const std::uint8_t button, const bool press)
    {
        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA);
        encoded.push_back(0x10 | (device & 0x0F));
        encoded.push_back(0x08);
        encoded.push_back(button & 0x7F);
        encoded.push_back(press ? 0x7F : 0x00);
        encoded.push_back(SYSEX_END);
    }

    static void encode_sysex_bulk_header(std::vector<std::uint8_t>& encoded, const std::uint8_t device, const std::uint8_t group, const std::uint8_t length_high, const std::uint8_t length_low)
    {
        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA);
        encoded.push_back(0x00 | (device & 0x0F));
        encoded.push_back(group & 0x7F);
        encoded.push_back(length_high & 0x7F);
        encoded.push_back(length_low & 0x7F);
    }

    static void encode_sysex_bulk_finish(std::vector<std::uint8_t>& encoded, const std::uint8_t* payload, const std::size_t payload_length)
    {
        encoded.insert(encoded.end(), payload, payload + payload_length);
        encoded.push_back(compute_sysex_checksum(payload, payload_length) & 0x7F);
        encoded.push_back(SYSEX_END);
    }
}

void yamaha_dx7::encode_note_off(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x80 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(0x00);
}

bool yamaha_dx7::decode_note_off(
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

void yamaha_dx7::encode_note_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note,
    const integral<std::uint8_t, 0, 127> velocity)
{
    encoded.push_back(0x90 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(velocity.value() & 0x7F);
}

bool yamaha_dx7::decode_note_on(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 15>& channel,
    integral<std::uint8_t, 0, 127>& note,
    integral<std::uint8_t, 0, 127>& velocity)
{
    if (encoded.size() != 3) {
        return false;
    }
    if ((encoded[0] & 0xF0) != 0x90) {
        return false;
    }

    channel = encoded[0] & 0x0F;
    note = encoded[1] & 0x7F;
    velocity = encoded[2] & 0x7F;

    return true;
}

void yamaha_dx7::encode_program_change(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 31> program)
{
    encoded.push_back(0xC0 | (channel.value() & 0x0F));
    encoded.push_back(program.value() & 0x7F);
}

bool yamaha_dx7::decode_program_change(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 15>& channel,
    integral<std::uint8_t, 0, 31>& program)
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

void yamaha_dx7::encode_pitchbend(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint16_t, 0, 16383, 8192> pitchbend)
{
    encoded.push_back(0xE0 | (channel.value() & 0x0F));
    encoded.push_back(static_cast<std::uint8_t>(pitchbend.value() & 0x7F));
    encoded.push_back(static_cast<std::uint8_t>((pitchbend.value() >> 7) & 0x7F));
}

bool yamaha_dx7::decode_pitchbend(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 15>& channel,
    integral<std::uint16_t, 0, 16383, 8192>& pitchbend)
{
    if (encoded.size() != 3) {
        return false;
    }
    if ((encoded[0] & 0xF0) != 0xE0) {
        return false;
    }

    channel = encoded[0] & 0x0F;
    pitchbend = ((encoded[2] & 0x7F) << 7) | encoded[1] & 0x7F;

    return true;
}

bool yamaha_dx7::decode_channel_pressure(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 15>& channel,
    integral<std::uint8_t, 0, 127>& pressure)
{
    if (encoded.size() != 2) {
        return false;
    }
    if ((encoded[0] & 0xF0) != 0xD0) {
        return false;
    }

    channel = encoded[0] & 0x0F;
    pressure = encoded[1] & 0x7F;

    return true;
}

void yamaha_dx7::encode_op_envelope_generator_rate_1(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_1, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_rate_2(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_2, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_rate_3(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_3, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_rate_4(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_4, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_level_1(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_1, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_level_2(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_2, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_level_3(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_3, data.value());
}

void yamaha_dx7::encode_op_envelope_generator_level_4(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_4, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_breakpoint(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_BREAKPOINT, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_left_depth(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_DEPTH, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_right_depth(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_DEPTH, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_left_curve(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 3> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_CURVE, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_right_curve(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 3> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_CURVE, data.value());
}

void yamaha_dx7::encode_op_keyboard_scaling_rate(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_KEYBOARD_SCALING_RATE, data.value());
}

void yamaha_dx7::encode_op_amplitude_modulation_sensitivity(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 3> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_AMPLITUDE_MODULATION_SENSITIVITY, data.value());
}

void yamaha_dx7::encode_op_velocity_sensitivity(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_VELOCITY_SENSITIVITY, data.value());
}

void yamaha_dx7::encode_op_output_level(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_OUTPUT_LEVEL, data.value());
}

void yamaha_dx7::encode_op_oscillator_mode(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_OSCILLATOR_MODE, data.value());
}

void yamaha_dx7::encode_op_oscillator_coarse(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 31> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_OSCILLATOR_COARSE, data.value());
}

void yamaha_dx7::encode_op_oscillator_fine(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_OSCILLATOR_FINE, data.value());
}

void yamaha_dx7::encode_op_oscillator_detune(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 5> op,
    const integral<std::uint8_t, 0, 14, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, (5 - op.value()) * SYSEX_VOICE_OP_BLOCK_STRIDE + SYSEX_VOICE_OP_OSCILLATOR_DETUNE, data.value());
}

void yamaha_dx7::encode_pitch_envelope_rate_1(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_RATE_1, data.value());
}

void yamaha_dx7::encode_pitch_envelope_rate_2(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_RATE_2, data.value());
}

void yamaha_dx7::encode_pitch_envelope_rate_3(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_RATE_3, data.value());
}

void yamaha_dx7::encode_pitch_envelope_rate_4(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_RATE_4, data.value());
}

void yamaha_dx7::encode_pitch_envelope_level_1(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_1, data.value());
}

void yamaha_dx7::encode_pitch_envelope_level_2(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_2, data.value());
}

void yamaha_dx7::encode_pitch_envelope_level_3(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_3, data.value());
}

void yamaha_dx7::encode_pitch_envelope_level_4(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_4, data.value());
}

void yamaha_dx7::encode_algorithm_mode(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 31> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_ALGORITHM_MODE, data.value());
}

void yamaha_dx7::encode_algorithm_feedback(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_ALGORITHM_FEEDBACK, data.value());
}

void yamaha_dx7::encode_oscillator_key_sync(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_OSCILLATOR_KEY_SYNC, data.value());
}

void yamaha_dx7::encode_lfo_waveform(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 4> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_WAVEFORM, data.value());
}

void yamaha_dx7::encode_lfo_speed(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_SPEED, data.value());
}

void yamaha_dx7::encode_lfo_delay(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_DELAY, data.value());
}

void yamaha_dx7::encode_lfo_pitch_modulation_depth(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_PITCH_MODULATION_DEPTH, data.value());
}

void yamaha_dx7::encode_lfo_amplitude_modulation_depth(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_AMPLITUDE_MODULATION_DEPTH, data.value());
}

void yamaha_dx7::encode_lfo_sync(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_LFO_SYNC, data.value());
}

void yamaha_dx7::encode_pitch_modulation_sensitivity(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_PITCH_MODULATION_SENSITIVITY, data.value());
}

void yamaha_dx7::encode_transpose_semitones(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 48, 24> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_TRANSPOSE, data.value());
}

void yamaha_dx7::encode_op_enable_mask(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0x00, 0x3F, 0x3F> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_OP_ENABLE_MASK, data.value());
}

void yamaha_dx7::encode_patch_name(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const std::array<char, 10>& data)
{
    for (std::size_t _char_index = 0; _char_index < 10; ++_char_index) {
        encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_VOICE, SYSEX_VOICE_VOICE_NAME_1 + _char_index, static_cast<std::uint8_t>(data[_char_index]));
    }
}

void yamaha_dx7::encode_mono_poly_mode(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_MONO_POLY_MODE, data.value());
}

void yamaha_dx7::encode_pitchbend_range_semitones(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 12, 2> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_pitchbend_RANGE, data.value());
}

void yamaha_dx7::encode_pitchbend_step(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 12> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_pitchbend_STEP, data.value());
}

void yamaha_dx7::encode_portamento_mode(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_PORTAMENTO_MODE, data.value());
}

void yamaha_dx7::encode_portamento_glissando(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_PORTAMENTO_GLISSANDO, data.value());
}

void yamaha_dx7::encode_portamento_time(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_PORTAMENTO_TIME, data.value());
}

void yamaha_dx7::encode_modulation_wheel_range(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_MODULATION_WHEEL_RANGE, data.value());
}

void yamaha_dx7::encode_modulation_wheel_assign(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_MODULATION_WHEEL_ASSIGN, data.value());
}

void yamaha_dx7::encode_foot_controller_range(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_FOOT_CONTROLLER_RANGE, data.value());
}

void yamaha_dx7::encode_foot_controller_assign(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_FOOT_CONTROLLER_ASSIGN, data.value());
}

void yamaha_dx7::encode_breath_controller_range(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_BREATH_CONTROLLER_RANGE, data.value());
}

void yamaha_dx7::encode_breath_controller_assign(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_BREATH_CONTROLLER_ASSIGN, data.value());
}

void yamaha_dx7::encode_after_touch_controller_range(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 99> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_AFTER_TOUCH_RANGE, data.value());
}

void yamaha_dx7::encode_after_touch_controller_assign(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 7> data)
{
    encode_sysex_parameter(encoded, device.value(), SYSEX_GROUP_FUNCTION, SYSEX_GLOBAL_AFTER_TOUCH_ASSIGN, data.value());
}

void yamaha_dx7::encode_button_voice(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 31> voice,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_1 + voice.value(), data.value());
}

void yamaha_dx7::encode_button_store(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_STORE, data.value());
}

void yamaha_dx7::encode_button_memory_protect_internal(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_MEMORY_PROTECT_INTERNAL, data.value());
}

void yamaha_dx7::encode_button_memory_protect_cartridge(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_MEMORY_PROTECT_CARTRIDGE, data.value());
}

void yamaha_dx7::encode_button_op_select(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_OPERATOR_SELECT, data.value());
}

void yamaha_dx7::encode_button_edit_compare(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_EDIT_COMPARE, data.value());
}

void yamaha_dx7::encode_button_memory_select_internal(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_MEMORY_SELECT_INTERNAL, data.value());
}

void yamaha_dx7::encode_button_memory_select_cartridge(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_MEMORY_SELECT_CARTRIDGE, data.value());
}

void yamaha_dx7::encode_button_function(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_FUNCTION, data.value());
}

void yamaha_dx7::encode_button_no(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_NO, data.value());
}

void yamaha_dx7::encode_button_yes(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const integral<std::uint8_t, 0, 1> data)
{
    encode_sysex_button(encoded, device.value(), SYSEX_BUTTON_YES, data.value());
}

void yamaha_dx7::encode_voice_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const voice_patch& data)
{
    std::array<std::uint8_t, 155> _vced {};
    std::uint8_t* _voice_ptr = _vced.data();

    for (std::size_t _op_reversed_index = 0; _op_reversed_index < 6; ++_op_reversed_index) {
        const std::size_t _op_index = 5 - _op_reversed_index;
        const std::size_t _op_base = static_cast<std::size_t>(_op_reversed_index) * SYSEX_VOICE_OP_BLOCK_STRIDE;
        std::uint8_t* _op_ptr = _voice_ptr + _op_base;

        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_1] = data.op_envelope_generator_rate_1[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_2] = data.op_envelope_generator_rate_2[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_3] = data.op_envelope_generator_rate_3[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_RATE_4] = data.op_envelope_generator_rate_4[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_1] = data.op_envelope_generator_level_1[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_2] = data.op_envelope_generator_level_2[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_3] = data.op_envelope_generator_level_3[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_ENVELOPE_GENERATOR_LEVEL_4] = data.op_envelope_generator_level_4[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_BREAKPOINT] = data.op_keyboard_scaling_breakpoint[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_DEPTH] = data.op_keyboard_scaling_left_depth[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_DEPTH] = data.op_keyboard_scaling_right_depth[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_LEFT_CURVE] = data.op_keyboard_scaling_left_curve[_op_index].value() & 0x03;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_RIGHT_CURVE] = data.op_keyboard_scaling_right_curve[_op_index].value() & 0x03;
        _op_ptr[SYSEX_VOICE_OP_KEYBOARD_SCALING_RATE] = data.op_keyboard_scaling_rate[_op_index].value() & 0x07;
        _op_ptr[SYSEX_VOICE_OP_AMPLITUDE_MODULATION_SENSITIVITY] = data.op_amplitude_modulation_sensitivity[_op_index].value() & 0x03;
        _op_ptr[SYSEX_VOICE_OP_VELOCITY_SENSITIVITY] = data.op_velocity_sensitivity[_op_index].value() & 0x07;
        _op_ptr[SYSEX_VOICE_OP_OUTPUT_LEVEL] = data.op_output_level[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_OSCILLATOR_MODE] = data.op_oscillator_mode[_op_index].value() & 0x01;
        _op_ptr[SYSEX_VOICE_OP_OSCILLATOR_COARSE] = data.op_oscillator_coarse[_op_index].value() & 0x1F;
        _op_ptr[SYSEX_VOICE_OP_OSCILLATOR_FINE] = data.op_oscillator_fine[_op_index].value() & 0x7F;
        _op_ptr[SYSEX_VOICE_OP_OSCILLATOR_DETUNE] = data.op_oscillator_detune[_op_index].value() & 0x0F;
    }

    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_RATE_1] = data.pitch_envelope_rate_1.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_RATE_2] = data.pitch_envelope_rate_2.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_RATE_3] = data.pitch_envelope_rate_3.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_RATE_4] = data.pitch_envelope_rate_4.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_1] = data.pitch_envelope_level_1.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_2] = data.pitch_envelope_level_2.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_3] = data.pitch_envelope_level_3.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_PITCH_ENVELOPE_LEVEL_4] = data.pitch_envelope_level_4.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_ALGORITHM_MODE] = data.algorithm_mode.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_ALGORITHM_FEEDBACK] = data.algorithm_feedback.value() & 0x07;
    _voice_ptr[SYSEX_VOICE_OSCILLATOR_KEY_SYNC] = data.oscillator_key_sync.value();
    _voice_ptr[SYSEX_VOICE_LFO_SPEED] = data.lfo_speed.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_LFO_DELAY] = data.lfo_delay.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_LFO_PITCH_MODULATION_DEPTH] = data.lfo_pitch_modulation_depth.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_LFO_AMPLITUDE_MODULATION_DEPTH] = data.lfo_amplitude_modulation_depth.value() & 0x7F;
    _voice_ptr[SYSEX_VOICE_LFO_SYNC] = data.lfo_sync.value();
    _voice_ptr[SYSEX_VOICE_LFO_WAVEFORM] = data.lfo_waveform_mode.value() & 0x07;
    _voice_ptr[SYSEX_VOICE_PITCH_MODULATION_SENSITIVITY] = data.pitch_modulation_sensitivity.value() & 0x07;
    _voice_ptr[SYSEX_VOICE_TRANSPOSE] = data.transpose_semitones.value() & 0x7F;

    for (std::size_t _char_index = 0; _char_index < 10; ++_char_index) {
        _voice_ptr[SYSEX_VOICE_VOICE_NAME_1 + _char_index] = static_cast<std::uint8_t>(data.voice_name[_char_index]) & 0x7F;
    }

    encode_sysex_bulk_header(encoded, device.value(), SYSEX_VCED_SINGLE, SYSEX_VCED_LENGTH_HIGH, SYSEX_VCED_LENGTH_LOW);
    encode_sysex_bulk_finish(encoded, _vced.data(), _vced.size());
}

void yamaha_dx7::encode_voice_patch_bank(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> device,
    const std::array<voice_patch, 32>& data)
{
    std::vector<std::uint8_t> _vmem;
    _vmem.resize(32 * 128, 0);

    for (std::size_t _voice_index = 0; _voice_index < 32; ++_voice_index) {
        std::uint8_t* _voice_ptr = _vmem.data() + _voice_index * 128;

        for (std::size_t _op_reversed_index = 0; _op_reversed_index < 6; ++_op_reversed_index) {
            const std::size_t _op_index = 5 - _op_reversed_index;
            const std::size_t _op_base = _op_reversed_index * 17;
            std::uint8_t* _op_ptr = _voice_ptr + _op_base;

            _op_ptr[0] = data[_voice_index].op_envelope_generator_rate_1[_op_index].value() & 0x7F;
            _op_ptr[1] = data[_voice_index].op_envelope_generator_rate_2[_op_index].value() & 0x7F;
            _op_ptr[2] = data[_voice_index].op_envelope_generator_rate_3[_op_index].value() & 0x7F;
            _op_ptr[3] = data[_voice_index].op_envelope_generator_rate_4[_op_index].value() & 0x7F;
            _op_ptr[4] = data[_voice_index].op_envelope_generator_level_1[_op_index].value() & 0x7F;
            _op_ptr[5] = data[_voice_index].op_envelope_generator_level_2[_op_index].value() & 0x7F;
            _op_ptr[6] = data[_voice_index].op_envelope_generator_level_3[_op_index].value() & 0x7F;
            _op_ptr[7] = data[_voice_index].op_envelope_generator_level_4[_op_index].value() & 0x7F;
            _op_ptr[8] = data[_voice_index].op_keyboard_scaling_breakpoint[_op_index].value() & 0x7F;
            _op_ptr[9] = data[_voice_index].op_keyboard_scaling_left_depth[_op_index].value() & 0x7F;
            _op_ptr[10] = data[_voice_index].op_keyboard_scaling_right_depth[_op_index].value() & 0x7F;
            _op_ptr[11] = ((data[_voice_index].op_keyboard_scaling_right_curve[_op_index].value() & 0x03) << 2) | (data[_voice_index].op_keyboard_scaling_left_curve[_op_index].value() & 0x03); // [3:2]=right, [1:0]=left
            _op_ptr[12] = ((data[_voice_index].op_oscillator_detune[_op_index].value() & 0x0F) << 3) | (data[_voice_index].op_keyboard_scaling_rate[_op_index].value() & 0x07);
            _op_ptr[13] = ((data[_voice_index].op_velocity_sensitivity[_op_index].value() & 0x07) << 2) | (data[_voice_index].op_amplitude_modulation_sensitivity[_op_index].value() & 0x03);
            _op_ptr[14] = data[_voice_index].op_output_level[_op_index].value() & 0x7F;
            _op_ptr[15] = ((data[_voice_index].op_oscillator_coarse[_op_index].value() & 0x1F) << 1) | (data[_voice_index].op_oscillator_mode[_op_index].value() & 0x01);
            _op_ptr[16] = data[_voice_index].op_oscillator_fine[_op_index].value() & 0x7F;
        }

        _voice_ptr[102] = data[_voice_index].pitch_envelope_rate_1.value() & 0x7F;
        _voice_ptr[103] = data[_voice_index].pitch_envelope_rate_2.value() & 0x7F;
        _voice_ptr[104] = data[_voice_index].pitch_envelope_rate_3.value() & 0x7F;
        _voice_ptr[105] = data[_voice_index].pitch_envelope_rate_4.value() & 0x7F;
        _voice_ptr[106] = data[_voice_index].pitch_envelope_level_1.value() & 0x7F;
        _voice_ptr[107] = data[_voice_index].pitch_envelope_level_2.value() & 0x7F;
        _voice_ptr[108] = data[_voice_index].pitch_envelope_level_3.value() & 0x7F;
        _voice_ptr[109] = data[_voice_index].pitch_envelope_level_4.value() & 0x7F;
        _voice_ptr[110] = data[_voice_index].algorithm_mode.value() & 0x7F;
        _voice_ptr[111] = (data[_voice_index].oscillator_key_sync.value() << 3) | (data[_voice_index].algorithm_feedback.value() & 0x07);
        _voice_ptr[112] = data[_voice_index].lfo_speed.value() & 0x7F;
        _voice_ptr[113] = data[_voice_index].lfo_delay.value() & 0x7F;
        _voice_ptr[114] = data[_voice_index].lfo_pitch_modulation_depth.value() & 0x7F;
        _voice_ptr[115] = data[_voice_index].lfo_amplitude_modulation_depth.value() & 0x7F;
        _voice_ptr[116] = ((data[_voice_index].lfo_waveform_mode.value() & 0x07) >> 4) | ((data[_voice_index].lfo_sync.value() & 0x01) >> 3) | (data[_voice_index].pitch_modulation_sensitivity.value() & 0x07);
        _voice_ptr[117] = data[_voice_index].transpose_semitones.value() & 0x7F;
        for (std::size_t _char_index = 0; _char_index < 10; ++_char_index) {
            _voice_ptr[118 + _char_index] = static_cast<std::uint8_t>(data[_voice_index].voice_name[_char_index]) & 0x7F;
        }
    }

    encode_sysex_bulk_header(encoded, device.value(), SYSEX_VMEM_BANK, SYSEX_VMEM_LENGTH_HIGH, SYSEX_VMEM_LENGTH_LOW);
    encode_sysex_bulk_finish(encoded, _vmem.data(), _vmem.size());
}

bool yamaha_dx7::decode_voice_patch_bank(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 15>& device,
    std::array<voice_patch, 32>& data)
{
    if (encoded.size() < 8 || encoded[0] != SYSEX_START || encoded[1] != SYSEX_YAMAHA || encoded.back() != SYSEX_END) {
        return false;
    }

    const bool _vmem_byte_is_correct = (encoded[2] & 0x70) == 0x00;
    if (!_vmem_byte_is_correct) {
        return false;
    }

    const std::uint8_t _header_group = encoded[3] & 0x7F;
    const std::uint8_t _header_length_high = encoded[4] & 0x7F;
    const std::uint8_t _header_length_low = encoded[5] & 0x7F;
    const std::uint8_t _header_payload_offset = 6;
    const std::size_t _header_payload_length = encoded.size() - 6 - 1 - 1;
    if (_header_payload_length == 0) {
        return false;
    }

    const std::size_t _checksum_index = encoded.size() - 2;
    const std::uint8_t _checksum_calculation = compute_sysex_checksum(encoded.data() + _header_payload_offset, _header_payload_length);
    if ((encoded[_checksum_index] & 0x7F) != _checksum_calculation) {
        return false;
    }

    if (_header_group != SYSEX_VMEM_BANK || _header_length_high != SYSEX_VMEM_LENGTH_HIGH || _header_length_low != SYSEX_VMEM_LENGTH_LOW) {
        return false;
    }

    if (_header_payload_length != 4096) {
        return false;
    }

    const std::uint8_t* _bank_ptr = encoded.data() + _header_payload_offset;
    for (std::size_t _voice_index = 0; _voice_index < 32; ++_voice_index) {

        const std::uint8_t* _voice_ptr = _bank_ptr + _voice_index * 128;
        for (std::size_t _op_reversed_index = 0; _op_reversed_index < 6; ++_op_reversed_index) {

            const std::size_t _op_base = _op_reversed_index * 17;
            const std::size_t _op_index = 5 - _op_reversed_index;
            const std::uint8_t* _op_ptr = _voice_ptr + _op_base;

            data[_voice_index].op_envelope_generator_rate_1[_op_index] = _op_ptr[0];
            data[_voice_index].op_envelope_generator_rate_2[_op_index] = _op_ptr[1];
            data[_voice_index].op_envelope_generator_rate_3[_op_index] = _op_ptr[2];
            data[_voice_index].op_envelope_generator_rate_4[_op_index] = _op_ptr[3];
            data[_voice_index].op_envelope_generator_level_1[_op_index] = _op_ptr[4];
            data[_voice_index].op_envelope_generator_level_2[_op_index] = _op_ptr[5];
            data[_voice_index].op_envelope_generator_level_3[_op_index] = _op_ptr[6];
            data[_voice_index].op_envelope_generator_level_4[_op_index] = _op_ptr[7];
            data[_voice_index].op_keyboard_scaling_breakpoint[_op_index] = _op_ptr[8];
            data[_voice_index].op_keyboard_scaling_left_depth[_op_index] = _op_ptr[9];
            data[_voice_index].op_keyboard_scaling_right_depth[_op_index] = _op_ptr[10];
            data[_voice_index].op_keyboard_scaling_left_curve[_op_index] = _op_ptr[11] & 0x03;
            data[_voice_index].op_keyboard_scaling_right_curve[_op_index] = (_op_ptr[11] >> 2) & 0x03;
            data[_voice_index].op_keyboard_scaling_rate[_op_index] = _op_ptr[12] & 0x07;
            data[_voice_index].op_amplitude_modulation_sensitivity[_op_index] = _op_ptr[13] & 0x03;
            data[_voice_index].op_velocity_sensitivity[_op_index] = (_op_ptr[13] >> 2) & 0x07;
            data[_voice_index].op_output_level[_op_index] = _op_ptr[14];
            data[_voice_index].op_oscillator_mode[_op_index] = _op_ptr[15] & 0x01;
            data[_voice_index].op_oscillator_coarse[_op_index] = (_op_ptr[15] >> 1) & 0x1F;
            data[_voice_index].op_oscillator_fine[_op_index] = _op_ptr[16];
            data[_voice_index].op_oscillator_detune[_op_index] = (_op_ptr[12] >> 3) & 0x0F;
        }

        data[_voice_index].pitch_envelope_rate_1 = _voice_ptr[102];
        data[_voice_index].pitch_envelope_rate_2 = _voice_ptr[103];
        data[_voice_index].pitch_envelope_rate_3 = _voice_ptr[104];
        data[_voice_index].pitch_envelope_rate_4 = _voice_ptr[105];
        data[_voice_index].pitch_envelope_level_1 = _voice_ptr[106];
        data[_voice_index].pitch_envelope_level_2 = _voice_ptr[107];
        data[_voice_index].pitch_envelope_level_3 = _voice_ptr[108];
        data[_voice_index].pitch_envelope_level_4 = _voice_ptr[109];
        data[_voice_index].algorithm_mode = _voice_ptr[110] & 0x7F;
        data[_voice_index].algorithm_feedback = _voice_ptr[111] & 0x07;
        data[_voice_index].oscillator_key_sync = (_voice_ptr[111] >> 3) & 0x01;
        data[_voice_index].lfo_waveform_mode = (_voice_ptr[116] >> 1) & 0x07;
        data[_voice_index].lfo_speed = _voice_ptr[112];
        data[_voice_index].lfo_delay = _voice_ptr[113];
        data[_voice_index].lfo_pitch_modulation_depth = _voice_ptr[114];
        data[_voice_index].lfo_amplitude_modulation_depth = _voice_ptr[115];
        data[_voice_index].lfo_sync = _voice_ptr[116] & 0x01;
        data[_voice_index].pitch_modulation_sensitivity = (_voice_ptr[116] >> 4) & 0x07;
        data[_voice_index].transpose_semitones = _voice_ptr[117];
        for (std::size_t _name_index = 0; _name_index < 10; ++_name_index) {
            data[_voice_index].voice_name[_name_index] = static_cast<char>(_voice_ptr[118 + _name_index]);
        }
    }

    device = encoded[2] & 0x0F;
    return true;
}
}
