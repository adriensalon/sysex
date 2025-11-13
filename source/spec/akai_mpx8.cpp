#include <midispec/spec/akai_mpx8.hpp>

/// User manual at
/// https://www.bhphotovideo.com/lit_files/84745.pdf

namespace midispec {
namespace akai_mpx8 {

    namespace channel_common {

        void encode_note_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note,
            const integral<std::uint8_t, 0, 127> velocity)
        {
            encoded.push_back(0x80 | (channel.value() & 0x0F));
            encoded.push_back(note.value() & 0x7F);
            encoded.push_back(velocity.value() & 0x7F);
        }

        void encode_note_on(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note,
            const integral<std::uint8_t, 0, 127> velocity)
        {
            encoded.push_back(0x90 | (channel.value() & 0x0F));
            encoded.push_back(note.value() & 0x7F);
            encoded.push_back(velocity.value() & 0x7F);
        }

        bool decode_note_off(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note,
            integral<std::uint8_t, 0, 127>& velocity)
        {
            if (encoded.size() != 3) {
                return false;
            }
            if ((encoded[0] & 0xF0) != 0x80) {
                return false;
            }

            channel = encoded[0] & 0x0F;
            note = encoded[1] & 0x7F;
            velocity = encoded[2] & 0x7F;

            return true;
        }

        bool decode_note_on(
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

        bool decode_note_aftertouch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note,
            integral<std::uint8_t, 0, 127>& aftertouch)
        {
            if (encoded.size() != 3) {
                return false;
            }
            if ((encoded[0] & 0xF0) != 0xA0) {
                return false;
            }
            if ((encoded[1] | encoded[2]) & 0x80) {
                return false;
            }

            channel = encoded[0] & 0x0F;
            note = encoded[1] & 0x7F;
            aftertouch = encoded[2] & 0x7F;

            return true;
        }
    }

    namespace system_exclusive {

        static constexpr std::uint8_t SYSEX_START = 0xF0;
        static constexpr std::uint8_t SYSEX_END = 0xF7;
        static constexpr std::uint8_t SYSEX_AKAI = 0x7E;

        void encode_universal_inquiry_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 127> device)
        {
            encoded.push_back(SYSEX_START);
            encoded.push_back(SYSEX_AKAI);
            encoded.push_back(device.value() & 0x7F);
            encoded.push_back(0x06);
            encoded.push_back(0x01);
            encoded.push_back(SYSEX_END);
        }

        bool decode_universal_inquiry(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 127>& device,
            std::uint32_t& manufacturer,
            std::uint32_t& family,
            std::uint32_t& model,
            std::uint32_t& version)
        {
            if (encoded.size() < 15) {
                return false;
            }
            if (encoded[0] != SYSEX_START) {
                return false;
            }
            if (encoded[1] != SYSEX_AKAI) {
                return false;
            }
            if (encoded[3] != 0x06) {
                return false;
            }
            if (encoded[4] != 0x02) {
                return false;
            }
            if (encoded.back() != SYSEX_END) {
                return false;
            }
            for (std::size_t _index = 1; _index + 1 < encoded.size(); ++_index) {
                if (encoded[_index] & 0x80) {
                    return false;
                }
            }

            device = encoded[2] & 0x7F;
            std::size_t _index = 5;

            if (encoded[_index] == 0x00) {
                if (encoded.size() < _index + 3 + 2 + 2 + 4 + 1) {
                    return false;
                }
                manufacturer = (static_cast<std::uint32_t>(encoded[_index]) << 16) | (static_cast<std::uint32_t>(encoded[_index + 1]) << 8) | static_cast<std::uint32_t>(encoded[_index + 2]);
                _index += 3;

            } else {
                if (encoded.size() < _index + 1 + 2 + 2 + 4 + 1) {
                    return false;
                }
                manufacturer = static_cast<std::uint32_t>(encoded[_index]);
                _index += 1;
            }

            family = static_cast<std::uint32_t>(encoded[_index] | (encoded[_index + 1] << 8));
            _index += 2;

            model = static_cast<std::uint32_t>(encoded[_index] | (encoded[_index + 1] << 8));
            _index += 2;

            version = (static_cast<std::uint32_t>(encoded[_index]) << 24) | (static_cast<std::uint32_t>(encoded[_index + 1]) << 16) | (static_cast<std::uint32_t>(encoded[_index + 2]) << 8) | static_cast<std::uint32_t>(encoded[_index + 3]);
            
            return true;
        }

    }
}
}