#pragma once

#include <array>
#include <optional>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {
namespace korg_microkorg {

    namespace channel_common {

        /// @brief Encodes a note off message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        void encode_note_off(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note);

        /// @brief Encodes a note on message
        /// @param encoded Vector to append the encoded message to
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @param velocity MIDI velocity. In range [0, 127]
        void encode_note_on(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> channel,
            const integral<std::uint8_t, 0, 127> note,
            const integral<std::uint8_t, 0, 127> velocity);

        void encode_program_change(
            std::vector<uint8_t>& out,
            integral<uint8_t, 0, 15> ch,
            integral<uint8_t, 0, 127> program);

        void encode_pitchbend(
            std::vector<uint8_t>& out,
            integral<uint8_t, 0, 15> ch,
            integral<uint16_t, 0, 16383> bend);

        /// @brief Decodes a note off message
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @return true on success
        bool decode_note_off(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note);

        /// @brief Decodes a note on message
        /// @param encoded Vector to read the encoded message from
        /// @param channel Target channel number. In range [0, 15]
        /// @param note MIDI note. In range [0, 127]
        /// @param velocity MIDI velocity. In range [0, 127]
        /// @return true on success
        bool decode_note_on(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            integral<std::uint8_t, 0, 127>& note,
            integral<std::uint8_t, 0, 127>& velocity);

        bool decode_program_change(
            const std::vector<uint8_t>& in,
            integral<std::uint8_t, 0, 15>& channel,
            integral<uint8_t, 0, 127>& program);

        bool decode_pitchbend(
            const std::vector<uint8_t>& in,
            integral<uint8_t, 0, 15>& ch,
            integral<uint16_t, 0, 16383>& bend);

    }

    namespace channel_cc {

        // many CC that are virtual
        // CC#00–CC#95
    }

    namespace channel_nrpn {

        void encode_arpeggiator_enable(
            std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            const integral<std::uint8_t, 0, 127> data);

        void encode_arpeggiator_range(
            std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            const integral<std::uint8_t, 0, 127> data);

        void encode_arpeggiator_latch(
            std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            const integral<std::uint8_t, 0, 127> data);

        void encode_arpeggiator_type(
            std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            const integral<std::uint8_t, 0, 127> data);

        void encode_arpeggiator_gate(
            std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& channel,
            const integral<std::uint8_t, 0, 127> data);


        enum class arp_type : std::uint8_t { Up,
            Down,
            Alt1,
            Alt2,
            Random,
            Trigger };
        void encode_arp_type(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            arp_type type);

        // GATE: 0..127 mapped to discrete % table (spec’s mapping)
        void encode_arp_gate(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            integral<std::uint8_t, 0, 127> raw);

        // (optional helpers)
        std::uint8_t canonical_value_for(arp_type t); // 0,26,51,77,102,127
        std::uint8_t clamp_gate_for_tx(std::uint8_t v); // if you want to snap to the table

        // -------------------- Virtual Patch (Synth/Vocoder) --------------------
        // MSB 04, LSB 00..03 (sources), 08..0B (dests)

        using patch_slot = integral<std::uint8_t, 1, 4>;

        // Sources/Destinations are 0..127 with grouped semantics from the table.
        // You can define enums if you want stronger typing, but raw 0..127 is spec-compliant.
        void encode_patch_source(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            patch_slot slot,
            integral<std::uint8_t, 0, 127> source_val);

        void encode_patch_destination(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            patch_slot slot,
            integral<std::uint8_t, 0, 127> dest_val);

        // Vocoder “FC MOD SOURCE” shares MSB/LSB with PATCH1 SOURCE in vocoder context.
        // If you want a named helper:
        void encode_vocoder_fc_mod_source(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            integral<std::uint8_t, 0, 127> source_val);

        // -------------------- Vocoder CH PARAM --------------------
        // MSB 04, LSB 0x10..0x1F for LEVEL, 0x20..0x2F for PAN

        using vocoder_band = integral<std::uint8_t, 1, 16>;

        void encode_vocoder_ch_level(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            vocoder_band band, // 1..16
            integral<std::uint8_t, 0, 127> level); // 0..127

        // PAN: 0/1=L63 … 63=L01, 64=CNT, 65=R01 … 127=R63
        void encode_vocoder_ch_pan(std::vector<std::uint8_t>& out,
            integral<std::uint8_t, 0, 15> ch,
            vocoder_band band,
            integral<std::uint8_t, 0, 127> pan);
    }

    namespace system_common {

        void encode_all_notes_off(std::vector<std::uint8_t>& encoded);

        void encode_all_sound_off(std::vector<std::uint8_t>& encoded);

        void encode_reset_all_controllers(std::vector<std::uint8_t>& encoded);

        // decode sync pas clair

    }

    namespace system_exclusive {

        enum struct VoiceMode : std::uint8_t {
            Single = 0,
            Layer = 2,
            Vocoder = 3
        };

        enum struct DelayType : std::uint8_t {
            Stereo = 0,
            Cross = 1,
            LR = 2
        };

        enum struct ModFxType : std::uint8_t {
            ChorusFlanger = 0,
            Ensemble = 1,
            Phaser = 2
        };

        enum struct LfoWave : std::uint8_t {
            Saw = 0,
            Square = 1,
            Triangle = 2,
            SampleHold = 3
        };
        enum struct LfoKeySync : std::uint8_t {
            Off = 0,
            Timbre = 1,
            Voice = 2
        };

        enum struct Osc1Wave : std::uint8_t {
            Saw = 0,
            Square = 1,
            Triangle = 2,
            DWGS = 3,
            Noise = 4,
            AudioIn = 7
        };

        enum struct Osc2Wave : std::uint8_t {
            Saw = 0,
            Square = 1,
            Triangle = 2
        };

        enum struct Osc2ModSelect : std::uint8_t {
            Off = 0,
            Ring = 1,
            Sync = 2,
            RingSync = 3
        };

        enum struct FilterType : std::uint8_t {
            LPF24 = 0,
            LPF12 = 1,
            BPF12 = 2,
            HPF12 = 3
        };

        enum struct arpeggiator_type : std::uint8_t {
            up = 0,
            down = 1,
            alt_1 = 2,
            alt_2 = 3,
            random = 4,
            trigger = 5
        };

        enum struct arpeggiator_target : std::uint8_t {
            both = 0,
            timbre_1 = 1,
            timbre_2 = 2
        };

        struct synthetizer_block {
            // +0 MIDI channel (0..16; spec uses “-1 = GLB” – store 0..16 and treat 0x7F specially in coder)
            integral<std::uint8_t, 0, 127> midi_channel = 0;

            // +1 Assign/EG reset/Trigger/Key Priority (bitfields)
            // B6..7 assign: 0 Mono,1 Poly,2 Unison
            integral<std::uint8_t, 0, 2> assign_mode = 1;
            // B5 EG2 reset (0/1), B4 EG1 reset (0/1)
            bool eg2_reset = false;
            bool eg1_reset = false;
            // B3 Trigger Mode: 0 Single, 1 Multi (mono/unison use)
            bool trigger_multi = false;
            // B0..1 Key Priority: 0 Last (spec shows only Last; keep raw for future)
            integral<std::uint8_t, 0, 3> key_priority = 0;

            // +2 Unison Detune (0..99 cents both ways in Unison mode). We store signed –99..+99.
            integral<std::uint16_t, -99, 99> unison_detune = 0;

            // PITCH
            // +3 Tune: 64 +/-50 cents
            integral<std::uint16_t, -50, 50> tune_cents = 0;
            // +4 Bend Range: 64 +/-12 semitones
            integral<int8_t, -12, 12> bend_range = 2;
            // +5 Transpose: 64 +/-24 semitones
            integral<int8_t, -24, 24> transpose = 0;
            // +6 Vibrato Int: 64 +/-63
            integral<int8_t, -63, 63> vibrato_int = 0;

            // OSC1
            // +7 Wave (0..7) (DWGS uses +10)
            integral<std::uint8_t, 0, 7> osc1_wave = static_cast<std::uint8_t>(Osc1Wave::Saw);
            // +8 Waveform CTRL1 (0..127)
            integral<std::uint8_t, 0, 127> osc1_ctrl1 = 0;
            // +9 Waveform CTRL2 (0..127)
            integral<std::uint8_t, 0, 127> osc1_ctrl2 = 0;
            // +10 DWGS Wave (0..63) when osc1_wave == DWGS
            integral<std::uint8_t, 0, 63> osc1_dwgs = 0;
            // +11 dummy per spec

            // OSC2
            // +12 Mod Select (B4..5: 0 Off,1 Ring,2 Sync,3 RingSync), Wave (B0..1: 0 Saw,1 Sqr,2 Tri)
            integral<std::uint8_t, 0, 3> osc2_mod_select = static_cast<std::uint8_t>(Osc2ModSelect::Off);
            integral<std::uint8_t, 0, 2> osc2_wave = static_cast<std::uint8_t>(Osc2Wave::Saw);
            // +13 Semitone: 64 +/-24 semitones
            integral<int8_t, -24, 24> osc2_semitone = 0;
            // +14 Tune: 64 +/-63
            integral<int8_t, -63, 63> osc2_tune = 0;

            // PITCH (2)
            // +15 Portamento Time (0..127)
            integral<std::uint8_t, 0, 127> portamento = 0;

            // MIXER
            // +16 OSC1 level (0..127)
            integral<std::uint8_t, 0, 127> osc1_level = 100;
            // +17 OSC2 level (0..127)  (or Ext1 level for vocoder, but this is synth timbre)
            integral<std::uint8_t, 0, 127> osc2_level = 0;
            // +18 Noise level (0..127)
            integral<std::uint8_t, 0, 127> noise_level = 0;

            // FILTER
            // +19 Type (0..3)
            integral<std::uint8_t, 0, 3> filter_type = static_cast<std::uint8_t>(FilterType::LPF24);
            // +20 Cutoff (0..127)
            integral<std::uint8_t, 0, 127> filter_cutoff = 64;
            // +21 Resonance (0..127)
            integral<std::uint8_t, 0, 127> filter_resonance = 0;
            // +22 EG1 Intensity: 64 +/-63
            integral<int8_t, -63, 63> filter_eg1_int = 0;
            // +23 Velocity Sense (0 => none; spec notes “64=0”, we store signed –63..+63)
            integral<int8_t, -63, 63> filter_vel_sense = 0;
            // +24 Keyboard Track 64 +/-63
            integral<int8_t, -63, 63> filter_keytrack = 0;

            // AMP
            // +25 Level (0..127)
            integral<std::uint8_t, 0, 127> amp_level = 127;
            // +26 Panpot: 0..127 with center at 64, L64..127..R63 (keep raw 0..127)
            integral<std::uint8_t, 0, 127> amp_pan = 64;
            // +27 B6 Amp SW (EG2), B0 Distortion On/Off
            bool amp_eg2 = true;
            bool distortion = false;
            // +28 Velocity Sense (64=0 -> signed)
            integral<int8_t, -63, 63> amp_vel_sense = 0;
            // +29 Keyboard Track 64 +/-63
            integral<int8_t, -63, 63> amp_keytrack = 0;

            // EG1
            // +30..+33 A/D/S/R (0..127)
            integral<std::uint8_t, 0, 127> eg1_attack = 0;
            integral<std::uint8_t, 0, 127> eg1_decay = 0;
            integral<std::uint8_t, 0, 127> eg1_sustain = 127;
            integral<std::uint8_t, 0, 127> eg1_release = 0;

            // EG2
            // +34..+37 A/D/S/R (0..127)
            integral<std::uint8_t, 0, 127> eg2_attack = 0;
            integral<std::uint8_t, 0, 127> eg2_decay = 0;
            integral<std::uint8_t, 0, 127> eg2_sustain = 0;
            integral<std::uint8_t, 0, 127> eg2_release = 0;

            // LFO1
            // +38 KeySync: 0 Off,1 Timbre,2 Voice
            LfoKeySync lfo1_key_sync = LfoKeySync::Off;
            // +38 Wave: 0..3 (Saw,Squ,Tri,S/H)
            LfoWave lfo1_wave = LfoWave::Saw;
            // +39 Frequency (0..127)
            integral<std::uint8_t, 0, 127> lfo1_freq = 0;
            // +40 Tempo Sync (0/1)
            bool lfo1_tempo_sync = false;
            // +40 Sync Note 0..14 (spec T-5: 1/1..1/32)
            integral<std::uint8_t, 0, 14> lfo1_sync_note = 0;

            // LFO2
            // +41 KeySync / Wave like LFO1 (note extra “Sin,S/H” variant in spec: Saw, Sqr(+), Sin, S/H)
            LfoKeySync lfo2_key_sync = LfoKeySync::Off;
            // For LFO2 the waves list includes “Sin”; keep using LfoWave and map 2=Sin for this block.
            integral<std::uint8_t, 0, 3> lfo2_wave_raw = 0; // 0 Saw,1 Squ(+),2 Sin,3 S/H
            // +42 Frequency
            integral<std::uint8_t, 0, 127> lfo2_freq = 0;
            // +43 Tempo Sync flag and +43 Sync Note
            bool lfo2_tempo_sync = false;
            integral<std::uint8_t, 0, 14> lfo2_sync_note = 0;

            // PATCH mod matrix (1..4)
            // +44 Patch1 Dest (B4..7) 0..7, Source (B0..3) 0..7
            integral<std::uint8_t, 0, 7> patch1_dest = 0;
            integral<std::uint8_t, 0, 7> patch1_src = 0;
            // +45 Intensity 64 +/-63
            integral<int8_t, -63, 63> patch1_amt = 0;

            // +46/47 Patch2
            integral<std::uint8_t, 0, 7> patch2_dest = 0;
            integral<std::uint8_t, 0, 7> patch2_src = 0;
            integral<int8_t, -63, 63> patch2_amt = 0;

            // +48/49 Patch3
            integral<std::uint8_t, 0, 7> patch3_dest = 0;
            integral<std::uint8_t, 0, 7> patch3_src = 0;
            integral<int8_t, -63, 63> patch3_amt = 0;

            // +50/51 Patch4
            integral<std::uint8_t, 0, 7> patch4_dest = 0;
            integral<std::uint8_t, 0, 7> patch4_src = 0;
            integral<int8_t, -63, 63> patch4_amt = 0;

            // +52..+107 dummy
        };

        struct vocoder_block {
            integral<std::uint8_t, 0, 127> midi_channel = 0;

            // +1 Assign/EG reset/Trigger/Key priority (as in timbre)
            integral<std::uint8_t, 0, 2> assign_mode = 1;
            bool eg2_reset = false;
            bool eg1_reset = false;
            bool trigger_multi = false;
            integral<std::uint8_t, 0, 3> key_priority = 0;

            // +2 Unison Detune – only used in Unison (–99..+99)
            integral<std::uint16_t, -99, 99> unison_detune = 0;

            // PITCH
            integral<std::uint16_t, -50, 50> tune_cents = 0; // +3
            integral<int8_t, -12, 12> bend_range = 2; // +4
            integral<int8_t, -24, 24> transpose = 0; // +5
            integral<int8_t, -63, 63> vibrato_int = 0; // +6

            // OSC1 (wave 0..7, DWGS extra) for carrier
            integral<std::uint8_t, 0, 7> osc1_wave = static_cast<std::uint8_t>(Osc1Wave::Saw); // +7
            integral<std::uint8_t, 0, 127> osc1_ctrl1 = 0; // +8
            integral<std::uint8_t, 0, 127> osc1_ctrl2 = 0; // +9
            integral<std::uint8_t, 0, 63> osc1_dwgs = 0; // +10
            // +11 dummy

            // AUDIO IN1 block (the modulator input settings)
            // +12 B0 HPF Gate Enable (0/1). B1..7 not used.
            bool hpf_gate_enable = false;
            // +13 dummy

            // PITCH (2)
            // +14 (B7 not used), +14 B0..6 Portamento (0..127)
            integral<std::uint8_t, 0, 127> portamento = 0;

            // MIXER (carrier levels)
            integral<std::uint8_t, 0, 127> osc1_level = 0; // +15
            integral<std::uint8_t, 0, 127> ext1_level = 0; // +16  (external in level)
            integral<std::uint8_t, 0, 127> noise_level = 0; // +17

            // AUDIO IN1 (2): HPF/Envelope follower
            integral<std::uint8_t, 0, 127> hpf_level = 0; // +18
            integral<std::uint8_t, 0, 127> gate_sense = 0; // +19
            integral<std::uint8_t, 0, 127> gate_threshold = 0; // +20

            // FILTER (vocoder’s formant filter)
            integral<std::uint8_t, 0, 4> formant_shift = 0; // +21  (0..4 = 0,+1,+2,-1,-2)
            integral<int8_t, -63, 63> formant_cutoff = 0; // +22  (64±63)
            integral<std::uint8_t, 0, 127> formant_resonance = 0; // +23
            integral<std::uint8_t, 1, 7> formant_mod_source = 1; // +24  (1..7 = AEG..MIDI2), *T-13
            integral<int8_t, -63, 63> formant_intensity = 0; // +25

            // AMP
            integral<std::uint8_t, 0, 127> amp_level = 127; // +27
            integral<std::uint8_t, 0, 127> amp_direct_level = 0; // +28
            bool distortion = false; // +29 B0
            // +29 B1..7 not used
            integral<std::uint8_t, 0, 127> amp_vel_sense_raw = 64; // +30 (64=0)
            integral<int8_t, -63, 63> amp_keytrack = 0; // +31

            // EG1 (0..127), +32..+35
            integral<std::uint8_t, 0, 127> eg1_attack = 0;
            integral<std::uint8_t, 0, 127> eg1_decay = 0;
            integral<std::uint8_t, 0, 127> eg1_sustain = 127;
            integral<std::uint8_t, 0, 127> eg1_release = 0;

            // EG2 +36..+39
            integral<std::uint8_t, 0, 127> eg2_attack = 0;
            integral<std::uint8_t, 0, 127> eg2_decay = 0;
            integral<std::uint8_t, 0, 127> eg2_sustain = 0;
            integral<std::uint8_t, 0, 127> eg2_release = 0;

            // LFO1 (+40..+41/+42)
            LfoKeySync lfo1_key_sync = LfoKeySync::Off;
            LfoWave lfo1_wave = LfoWave::Saw;
            integral<std::uint8_t, 0, 127> lfo1_freq = 0;
            bool lfo1_tempo_sync = false; // +42 B7
            integral<std::uint8_t, 0, 14> lfo1_sync_note = 0; // +42 B0..4

            // LFO2 (+43..+45)
            LfoKeySync lfo2_key_sync = LfoKeySync::Off;
            integral<std::uint8_t, 0, 3> lfo2_wave_raw = 0; // 0 Saw,1 Squ(+),2 Sin,3 S/H
            integral<std::uint8_t, 0, 127> lfo2_freq = 0;
            bool lfo2_tempo_sync = false; // +45 B7
            integral<std::uint8_t, 0, 14> lfo2_sync_note = 0; // +45 B0..4

            // CH LEVEL array (band levels) — 10 bands labelled 0..9 in spec footer.
            std::array<integral<std::uint8_t, 0, 127>, 10> band_levels {}; // levels per band
        };

        struct patch {
            std::array<char, 12> voice_name;

            // 16 B4..5 Voice Mode (0 Single, 2 Layer, 3 Vocoder)
            VoiceMode voice_mode = VoiceMode::Single;

            // 17 Scale: key/type (raw 0..)
            integral<std::uint8_t, 0, 15> scale_key = 0; // 17 B4..7 (0=C)
            integral<std::uint8_t, 0, 15> scale_type = 0; // 17 B0..3 (0=Equal Temp)

            // 19 B7 Sync (0 Off / 1 On)
            bool delay_sync = false;
            // 19 B0..3 Time Base (0=1/64 .. per spec *T-1)
            integral<std::uint8_t, 0, 14> delay_time_base = 0;
            // 20 Delay Time (0..127)
            integral<std::uint8_t, 0, 127> delay_time = 0;
            // 21 Depth (0..127)
            integral<std::uint8_t, 0, 127> delay_depth = 0;
            // 22 Type (0..2)
            DelayType delay_type;

            // 23 LFO Speed (0..127)
            integral<std::uint8_t, 0, 127> modulation_effect_speed = 0;
            // 24 Depth (0..127)
            integral<std::uint8_t, 0, 127> modulation_effect_depth = 0;
            // 25 Type (0..2)
            ModFxType modulation_effect_type;

            integral<std::uint8_t, 0, 29> equalizer_high_frequency = 0;
            // 27 Hi Gain 64 +/-12
            integral<int8_t, -12, 12> equalizer_high_gain = 0;
            // 28 Low Freq index 0..29 (~40–1000Hz), spec table T-11
            integral<std::uint8_t, 0, 29> equalizer_low_frequency = 0;
            // 29 Low Gain 64 +/-12
            integral<int8_t, -12, 12> equalizer_low_gain = 0;

            // 14 B0..2 Trigger length (0..7 => 1..8 steps)
            integral<std::uint8_t, 0, 7> arpeggiator_trigger_length = 0;
            // 15 B0..7 Trigger pattern bitmask (step1..step8)
            uint8_t arpeggiator_trigger_pattern = 0;

            bool arpeggiator_on = false;
            // 32 B6 Latch
            bool arpeggiator_latch = false;
            // 32 B4..5 Target (0 Both,1 Timbre1,2 Timbre2)
            arpeggiator_target arpeggiator_target;
            // 32 B0 Key Sync
            bool arpeggiator_key_sync = false;
            // 33 B0..3 Type (0..5), spec *T-12 map
            arpeggiator_type arpeggiator_type;
            // 33 B4..7 Range (0..3 => 1..4 octaves)
            integral<std::uint8_t, 0, 3> arpeggiator_range = 0;
            // 34 Gate (0..100%), encoded 0..100
            integral<std::uint8_t, 0, 100> arpeggiator_gate = 0;
            // 35 Resolution selector 0..5 (1/24,1/16,1/12,1/8,1/6,1/4)
            integral<std::uint8_t, 0, 5> arpeggiator_resolution = 0;
            // 36 Swing (–100..+100%)
            integral<std::uint16_t, -100, 100> arpeggiator_swing = 0;
            // 30..31 Tempo MSB/LSB (20..300 BPM; 31 is “SEQ tempo” special)
            integral<uint16_t, 20, 300> arpeggiator_tempo_bpm = 120;
            // 37 Keyboard Octave (–3..+3 + special “0” positions; store raw –3..+3)
            integral<int8_t, -3, 3> arpeggiator_kbd_octave = 0;

            synthetizer_block timbre_1;
            std::optional<synthetizer_block> timbre_2;
            std::optional<vocoder_block> vocoder;
        };

        enum class velocity_mode_t : std::uint8_t { Curve = 0,
            Fixed = 1 };

        enum class position_t : std::uint8_t { PostKBD = 0,
            PreTG = 1 };

        struct global_patch {
            integral<std::uint16_t, 4300, 4500> master_tune_tenths_hz = 4400;

            // Master Transpose: –12..+12 semitones
            integral<std::int8_t, -12, 12> master_transpose = 0;

            velocity_mode_t velocity_mode = velocity_mode_t::Curve;
            integral<std::uint8_t, 1, 127> velocity_fixed = 100;
            position_t position = position_t::PostKBD;

            // AUDIO IN THRU (volatile, not saved by Write; always resets OFF at power-on)
            bool audio_in_thru = false;
            integral<std::uint8_t, 1, 16> midi_channel = 1;
            bool local_control_on = true;

            // MIDI Clock source: Internal / External / Auto
            enum class clock_t : std::uint8_t { Internal = 0,
                External = 1,
                Auto = 2 };
            clock_t clock_source = clock_t::Internal;

            // ---------- SHIFT: MIDI FILTER (p.60–61) ----------
            // Whether these categories are transmitted/received.
            struct midi_filter_t {
                bool program_change = true;
                bool pitch_bend = true;
                bool control_change = true;
                bool system_excl = true; // must be ON to Rx/Tx dumps
            } midi_filter {};

            // ---------- SHIFT: CONTROL CHANGE assignments (p.61, p.56 table) ----------
            // The microKORG lets you remap many panel controls to specific CC numbers.
            // This can get long; keep it extensible. Add entries as you support more.
            struct cc_assign {
                // which logical control this assignment refers to (your own enum/id)
                std::uint16_t control_id = 0;
                // assigned MIDI CC number (0..127), 128 means “unassigned”
                integral<std::uint16_t, 0, 128> cc = 128;
            };
            std::vector<cc_assign> control_change_map; // optional; empty = device defaults

            // ---------- SHIFT: WRITE PROTECT (p.68) ----------
            bool write_protect = false;
        };

        // master fine volume

        // master fine tuning

        void encode_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const patch& data);

        void encode_patch_bank(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const std::array<patch, 8>& data); // or 16 not sure if it counts A and B

        void encode_global_patch(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device,
            const global_patch& data);

        void encode_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device);

        void encode_patch_bank_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device);

        void encode_global_patch_request(
            std::vector<std::uint8_t>& encoded,
            const integral<std::uint8_t, 0, 15> device);

        bool decode_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            patch& data);

        bool decode_patch_bank(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            std::array<patch, 8>& data); // or 16 not sure if it counts A and B

        bool decode_global_patch(
            const std::vector<std::uint8_t>& encoded,
            integral<std::uint8_t, 0, 15>& device,
            global_patch& data);

    }

}
}