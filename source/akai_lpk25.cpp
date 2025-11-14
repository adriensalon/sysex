#include <midispec/akai_lpk25.hpp>

/// User manual at
/// https://www.manua.ls/akai/lpk25/manual.com

namespace midispec {

static_assert(has_note_off_v<akai_lpk25, capability::receive, capability::transmit>);
static_assert(has_note_on_v<akai_lpk25, capability::receive, capability::transmit>);

// channel common

void akai_lpk25::encode_note_off(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x80 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(0x00);
}

bool akai_lpk25::decode_note_off(
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

void akai_lpk25::encode_note_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 15> channel,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x90 | (channel.value() & 0x0F));
    encoded.push_back(note.value() & 0x7F);
    encoded.push_back(0x7F);
}

bool akai_lpk25::decode_note_on(
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

// system common

void akai_lpk25::encode_clock(std::vector<std::uint8_t>& encoded)
{
    encoded.push_back(0xF8);
}

void akai_lpk25::encode_song_position_pointer(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint16_t, 0, 16383> data)
{
    encoded.push_back(0xF2);
    encoded.push_back(static_cast<std::uint8_t>(data.value() & 0x7F));
    encoded.push_back(static_cast<std::uint8_t>((data.value() >> 7) & 0x7F));
}

void akai_lpk25::encode_continue(std::vector<std::uint8_t>& encoded)
{
    encoded.push_back(0xFB);
}

bool akai_lpk25::decode_reset(const std::vector<std::uint8_t>& encoded)
{
    if (encoded.size() != 1) {
        return false;
    }
    if (encoded[0] != 0xFF) {
        return false;
    }

    return true;
}

}