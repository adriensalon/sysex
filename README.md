# midispec

midispec aims at exposing, documenting and implementing MIDI capabilities from
a wide range of hardware. Design philosophy is to not abstract away from the capabilities
exposed by the hardware, and to provide documented programming interfaces per hardware.
Each value that passes through encoding is statically bounds checked and bounds are documented.
Naming stays consistent between same capabilities on different hardware. Capabilities are divided
into the same categories:
- channel voice messages (note on/off, program change, pitch bend etc...)
- CC messages
- NRPN messages
- system common messages (clock, active sens etc...)
- system exclusive messages

Each capability corresponds to an encode_capability() function if the hardware can receive it,
and to a decode_capability() function if the hardware can transmit it.

Tests that assert correctness and robustness of the implementation are conducted using minimal fuzzing.
All features exposed in the headers and can be asserted by a full roundtrip host > hardware > host correspond to a test.

## Supported hardware
- Akai LPK25 (no meaningful automated test can be conducted)
- Akai MPX8
- Korg microKORG
- Yamaha DX7 (tested on 25/11/12)
- Yamaha SPX90 (no meaningful automated test can be conducted)
- Yamaha TX81Z
