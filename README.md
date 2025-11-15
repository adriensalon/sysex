# midispec

midispec aims at exposing, documenting and implementing MIDI capabilities from
a wide range of hardware. Design philosophy is to not abstract away from the capabilities
exposed by the hardware, and to provide documented programming interfaces per hardware.
Each value that passes through encoding is statically bounds checked and bounds are documented.
Naming stays consistent between same capabilities on different hardware.

Each capability corresponds to an encode_capability() function if the hardware can receive it,
and to a decode_capability() function if the hardware can transmit it.

Tests that assert correctness and robustness of the implementation are conducted using minimal fuzzing.
All features exposed in the headers and can be asserted by a full roundtrip host > hardware > host correspond to a test.

## Supported hardware
- __Akai LPK25__ (no meaningful automated test can be conducted)
- __Akai MPX8__ (tested on 25/11/15)
- __Akai RythmWolf__ (no meaningful automated test can be conducted)
- __Novation Launchpad__ (no meaningful automated test can be conducted)
- __Novation Launchpad S__ (tested on 25/11/15)
- __Yamaha DX7__ (tested on 25/11/12)
- __Yamaha SPX90__ (no meaningful automated test can be conducted)
- __Yamaha TX81Z__ (tested on 25/11/16)
