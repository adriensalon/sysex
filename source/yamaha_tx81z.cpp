#include <midispec/yamaha_tx81z.hpp>

/// User manual at
/// https://device.report/m/f6b9725630ebc28a1920ae53461989d46b68527173e1eb8c19d1d4b9761697f2.pdf

namespace midispec {

static_assert(has_note_off_v<yamaha_tx81z, capability::receive>);
static_assert(has_note_on_v<yamaha_tx81z, capability::receive>);
static_assert(has_note_aftertouch_v<yamaha_tx81z, capability::receive>);
static_assert(has_program_change_v<yamaha_tx81z, capability::receive>);
static_assert(has_pitchbend_change_v<yamaha_tx81z, capability::receive>);
static_assert(has_all_notes_off_v<yamaha_tx81z, capability::receive>);
static_assert(has_active_sens_v<yamaha_tx81z, capability::receive>);
static_assert(has_voice_patch_v<yamaha_tx81z, capability::receive, capability::request, capability::transmit>);

// channel common

void yamaha_tx81z::encode_note_off(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x80 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(0x00);
}

void yamaha_tx81z::encode_note_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note,
    const integral<std::uint8_t, 0, 127> velocity)
{
    encoded.push_back(0x90 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(velocity.value() & 0x7F);
}

void yamaha_tx81z::encode_note_aftertouch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note,
    const integral<std::uint8_t, 0, 127> aftertouch)
{
    // TODO
}

void yamaha_tx81z::encode_program_change(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> program)
{
    encoded.push_back(0xC0 | (channel.value() & 0x0F));
    encoded.push_back(program.value() & 0x7F);
}

void yamaha_tx81z::encode_pitchbend_change(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint16_t, 0, 16383, 8192> pitchbend)
{
    encoded.push_back(0xE0 | (channel.value() & 0x0F));
    encoded.push_back(static_cast<std::uint8_t>(pitchbend.value() & 0x7F));
    encoded.push_back(static_cast<std::uint8_t>((pitchbend.value() >> 7) & 0x7F));
}

// channel CC

void yamaha_tx81z::encode_modulation_wheel(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_breath_controller(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_foot_controller(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_portamento_time(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_volume(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_pan(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_sustain(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

void yamaha_tx81z::encode_portamento(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> data)
{
}

// system common

void yamaha_tx81z::encode_all_notes_off(std::vector<std::uint8_t>& encoded)
{
}

void yamaha_tx81z::encode_active_sens(std::vector<std::uint8_t>& encoded)
{
}

// system exclusive

namespace {
    static constexpr std::uint8_t SYSEX_START = 0xF0;
    static constexpr std::uint8_t SYSEX_END = 0xF7;
    static constexpr std::uint8_t SYSEX_YAMAHA = 0x43;

    static constexpr std::uint8_t SYSEX_VCED_OP_ATTACK_RATE = 0;
    static constexpr std::uint8_t SYSEX_VCED_OP_DECAY_RATE_1 = 1;
    static constexpr std::uint8_t SYSEX_VCED_OP_DECAY_RATE_2 = 2;
    static constexpr std::uint8_t SYSEX_VCED_OP_RELEASE_RATE = 3;
    static constexpr std::uint8_t SYSEX_VCED_OP_DECAY_LEVEL_1 = 4;
    static constexpr std::uint8_t SYSEX_VCED_OP_LEVEL_SCALING = 5;
    static constexpr std::uint8_t SYSEX_VCED_OP_RATE_SCALING = 6;
    static constexpr std::uint8_t SYSEX_VCED_OP_ENVELOPE_GENERATOR_BIAS_SENSITIVITY = 7;
    static constexpr std::uint8_t SYSEX_VCED_OP_AMPLITUDE_MODULATION_ENABLE = 8;
    static constexpr std::uint8_t SYSEX_VCED_OP_KEY_VELOCITY_SENSITIVITY = 9;
    static constexpr std::uint8_t SYSEX_VCED_OP_OUTPUT_LEVEL = 10;
    static constexpr std::uint8_t SYSEX_VCED_OP_FREQUENCY = 11;
    static constexpr std::uint8_t SYSEX_VCED_OP_DETUNE = 12;

    static constexpr std::uint8_t SYSEX_VCED_ALGORITHM_MODE = 10;
    static constexpr std::uint8_t SYSEX_VCED_ALGORITHM_FEEDBACK = 10;
    static constexpr std::uint8_t SYSEX_VCED_LFO_SPEED = 10;
    static constexpr std::uint8_t SYSEX_VCED_LFO_DELAY = 10;
    static constexpr std::uint8_t SYSEX_VCED_PITCH_MODULATION_DEPTH = 10;
    static constexpr std::uint8_t SYSEX_VCED_AMPLITUDE_MODULATION_DEPTH = 10;

    static constexpr std::uint8_t SYSEX_ACED_OP_FIXED_FREQUENCY = 0;
    static constexpr std::uint8_t SYSEX_ACED_OP_FIXED_FREQUENCY_RANGE = 1;
    static constexpr std::uint8_t SYSEX_ACED_OP_FREQUENCY_RANGE_FINE = 2;
    static constexpr std::uint8_t SYSEX_ACED_OP_WAVEFORM = 3;
    static constexpr std::uint8_t SYSEX_ACED_OP_ENVELOPE_GENERATOR_SHIFT = 4;

    static constexpr std::uint8_t SYSEX_VCED_SIZE = 0x005D;

    static std::uint8_t compute_sysex_checksum(const std::uint8_t* data, const std::size_t length)
    {
        std::uint32_t _sum = 0;
        for (std::size_t _index = 0; _index < length; ++_index) {
            _sum += (data[_index] & 0x7F);
        }

        return (128 - (_sum & 0x7F)) & 0x7F;
    }

    static void sysex_open(std::vector<std::uint8_t>& encoded, const std::uint8_t device, const std::uint8_t function, const std::uint16_t size)
    {
        encoded.push_back(SYSEX_START);
        encoded.push_back(SYSEX_YAMAHA);
        encoded.push_back(0x10 | (device & 0x0F));
        encoded.push_back(function);
        encoded.push_back(static_cast<std::uint8_t>((size >> 8) & 0x7F));
        encoded.push_back(static_cast<std::uint8_t>((size) & 0x7F));
    }

    static void sysex_close(std::vector<uint8_t>& encoded, const std::size_t data_start_index)
    {
        const std::uint8_t* _data_ptr = encoded.data() + data_start_index;
        const std::size_t _data_size = encoded.size() - data_start_index;
        encoded.push_back(compute_sysex_checksum(_data_ptr, _data_size));
        encoded.push_back(SYSEX_END);
    }
}

void yamaha_tx81z::encode_voice_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const voice_patch& data)
{
    {
        // VCED
        std::array<std::uint8_t, SYSEX_VCED_SIZE> _vced;
        std::uint8_t* _voice_ptr = _vced.data();

        for (std::size_t _op_index = 3; _op_index >= 0; --_op_index) {
            std::uint8_t* _op_ptr = _vced.data() + 12 * _op_index;

            _op_ptr[SYSEX_VCED_OP_ATTACK_RATE] = data.op_attack_rate[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_DECAY_RATE_1] = data.op_decay_rate_1[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_DECAY_RATE_2] = data.op_decay_rate_2[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_RELEASE_RATE] = data.op_release_rate[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_DECAY_LEVEL_1] = data.op_decay_level_1[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_LEVEL_SCALING] = data.op_level_scaling[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_RATE_SCALING] = data.op_rate_scaling[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_ENVELOPE_GENERATOR_BIAS_SENSITIVITY] = data.op_envelope_generator_bias_sensitivity[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_AMPLITUDE_MODULATION_ENABLE] = data.op_amplitude_modulation_enable[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_KEY_VELOCITY_SENSITIVITY] = data.op_key_velocity_sensitivity[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_OUTPUT_LEVEL] = data.op_output_level[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_FREQUENCY] = data.op_frequency[_op_index].value();
            _op_ptr[SYSEX_VCED_OP_DETUNE] = data.op_detune[_op_index].value();
        }

        encoded.push_back(data.algorithm_mode.value());
        encoded.push_back(data.algorithm_feedback.value());
        encoded.push_back(data.lfo_speed.value());
        encoded.push_back(data.lfo_delay.value());
        encoded.push_back(data.pitch_modulation_depth.value());
        encoded.push_back(data.amplitude_modulation_depth.value());
        encoded.push_back(data.lfo_sync.value());
        encoded.push_back(data.lfo_wave.value());
        encoded.push_back(data.pitch_modulation_sensitivity.value());
        encoded.push_back(data.amplitude_modulation_sensitivity.value());
        encoded.push_back(data.transpose.value());
        encoded.push_back(data.poly_mono.value());
        encoded.push_back(data.pitchbend_range.value());
        encoded.push_back(data.portamento_mode.value());
        encoded.push_back(data.portamento_time.value());
        encoded.push_back(data.foot_controller_volume.value());
        encoded.push_back(data.sustain.value());
        encoded.push_back(data.portamento.value());
        encoded.push_back(data.chorus.value());
        encoded.push_back(data.modulation_wheel_pitch.value());
        encoded.push_back(data.modulation_wheel_amplitude.value());
        encoded.push_back(data.breath_controller_pitch.value());
        encoded.push_back(data.breath_controller_amplitude.value());
        encoded.push_back(data.breath_controller_pitch_bias.value());
        encoded.push_back(data.breath_controller_envelope_generator_bias.value());
        for (std::size_t _char_index = 0; _char_index < 10; ++_char_index) {
            encoded.push_back(static_cast<uint8_t>(data.voice_name[_char_index]));
        }
        for (std::size_t _empty_index = 0; _empty_index < 6; ++_empty_index) {
            encoded.push_back(0x00);
        }

        const std::size_t _data_start = encoded.size();
        encoded.insert(encoded.end(), _vced.begin(), _vced.end());
        sysex_close(encoded, _data_start);
    }

    {
        // ACED
        sysex_open(encoded, static_cast<std::uint8_t>(device), 0x7E, 0x0021);
        const size_t data_start = encoded.size();

        encoded.insert(encoded.end(), { 'L', 'M', ' ', ' ', '8', '9', '7', '6', 'A', 'E' });

        // for (std::size_t _op_index = 3; _op_index >= 0; --_op_index) {
        //     encoded.push_back(data.op_fixed_frequency[_op_index]);
        //     encoded.push_back(data.op_fixed_frequency_range[_op_index]);
        //     encoded.push_back(data.op_frequency_range_fine[_op_index]);
        //     encoded.push_back(data.op_waveform[_op_index]);
        //     encoded.push_back(data.op_envelope_generator_shift[_op_index]);
        // }

        // encoded.push_back(data.reverb_rate);
        // encoded.push_back(data.foot_controller_pitch);
        // encoded.push_back(data.foot_controller_amplitude);

        sysex_close(encoded, data_start);
    }
}

void yamaha_tx81z::encode_bank(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const std::array<voice_patch, 128>& data)
{
}

void yamaha_tx81z::encode_performance_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const performance_patch& data)
{
}

void yamaha_tx81z::encode_system_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const system_patch& data)
{
}

void yamaha_tx81z::encode_effect_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const system_patch& data)
{
}

void yamaha_tx81z::encode_program_change_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const std::array<integral<std::uint8_t, 0, 127>, 127>& data)
{
}

void yamaha_tx81z::encode_microtune_patch(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device,
    const microtune_patch& data)
{
}

void yamaha_tx81z::encode_voice_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_bank_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_performance_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_system_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_effect_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_program_change_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}

void yamaha_tx81z::encode_microtune_patch_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15>& device)
{
}
}