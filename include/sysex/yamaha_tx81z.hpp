#pragma once

#include <array>
#include <cstdint>
#include <vector>

namespace sysex {

/// @brief
namespace yamaha_tx81z {

    /// @brief Devices correspond to hardware units.
    /// Each hardware unit represent a device that can be selected directly on the hardware.
    /// Some hardware can be configured to receive messages from all devices.
    /// Devices can be used to link multiple hardware to a single MIDI input or output.
    /// Range is [0, 15]
    using device_id = std::uint8_t;

    enum struct algorithm : std::uint8_t { // TX81Z has 8 algorithms
        alg1 = 1,
        alg2,
        alg3,
        alg4,
        alg5,
        alg6,
        alg7,
        alg8
    };

    enum struct wave : std::uint8_t { // 8 operator waves
        sine = 0,
        half_sine,
        abs_sine,
        quarter_sine,
        alt_sine1,
        alt_sine2,
        alt_sine3,
        alt_sine4
    };

    /* ─────────────────────────
   Operator block (per-op)
   ───────────────────────── */
    struct op_eg_rates {
        std::uint8_t r1 {}, r2 {}, r3 {}, r4 {};
    }; // 0..99
    struct op_eg_levels {
        std::uint8_t l1 { 99 }, l2 {}, l3 {}, l4 {};
    }; // 0..99
    struct op_scaling {
        std::uint8_t break_point {}; // 0..99
        std::uint8_t left_depth {}; // 0..99
        std::uint8_t right_depth {}; // 0..99
        std::uint8_t left_curve {}; // 0..3
        std::uint8_t right_curve {}; // 0..3
        std::uint8_t rate_scaling {}; // 0..7
    };
    struct op_level_vel_sens {
        std::uint8_t output_level { 99 };
        std::uint8_t vel_sens {};
    }; // 0..99, 0..7
    struct op_osc {
        wave waveform { wave::sine };
        std::uint8_t coarse {}; // 0..31 (ratio or fixed)
        std::uint8_t fine {}; // 0..99
        std::int8_t detune {}; // -7..+7 (0..14 in SysEx)
        bool fixed_mode { false }; // fixed vs ratio
    };

    /* ─────────────────────────
   Voice (VCED + ACED)
   ───────────────────────── */
    struct lfo_block {
        std::uint8_t wave {}; // TX81Z has multiple LFO/vibrato gens; expose raw 0..?
        std::uint8_t speed {};
        std::uint8_t delay {};
        std::uint8_t pitch_mod_depth {};
        std::uint8_t amp_mod_depth {};
        bool key_sync {};
    };

    struct pitch_env {
        std::uint8_t r1 {}, r2 {}, r3 {}, r4 {};
        std::uint8_t l1 { 50 }, l2 { 50 }, l3 { 50 }, l4 { 50 };
    };

    struct vced { // “Voice Edit” core (DX21/27/100-compatible subset)
        std::array<op_eg_rates, 4> ops_rates {};
        std::array<op_eg_levels, 4> ops_levels {};
        std::array<op_scaling, 4> ops_scaling {};
        std::array<op_level_vel_sens, 4> ops_level_vel {};
        std::array<op_osc, 4> ops_osc {};

        pitch_env pitch {};
        algorithm algo { algorithm::alg1 };
        std::uint8_t feedback {}; // 0..7
        std::uint8_t transpose {}; // encoded 0..48 (24 = 0 semis)
        std::array<char, 10> name {}; // 10 ASCII (7-bit)
    };

    struct aced { // “Additional Voice Edit” (TX81Z extras: waves, more routings, etc.)
        // Expose raw bytes for now; you can split into named fields as you wire them.
        std::array<std::uint8_t, 23> bytes {};
    };

    struct single_voice { // VCED + ACED together = one editable voice
        vced v {};
        aced a {};
    };

    /* ─────────────────────────
   Bank and Performance
   ───────────────────────── */
    struct vmem_bank { // 32 voices (each = VCED+ACED)
        std::array<single_voice, 32> voices {};
    };

    struct pced { // performance edit buffer (multi/part setup)
        // Keep raw for first pass; TX81Z PCED is 120 bytes.
        std::array<std::uint8_t, 120> data {};
    };

    struct pmem_bank { // 24 internal + 8 initial performances = 32 * 76 + header
        // Represent as raw block for now (2450 total bytes w/ header+cs in bulk).
        std::array<std::uint8_t, 2442> data {}; // data only (per manual: 0x098Ah)
    };

    /* ─────────────────────────
   System & Tables
   ───────────────────────── */
    struct system_block { // “SYS” (basic receive ch, etc.)
        // Manual says SYS data size = 37 bytes (plus header+cs in bulk).
        std::array<std::uint8_t, 37> data {};
    };

    struct program_change_table { // I1..PF24 map (266 data bytes)
        std::array<std::uint8_t, 266> map {};
    };

    struct microtune_octave {
        std::array<std::uint8_t, 24> data {};
    }; // data=24
    struct microtune_fullkbd {
        std::array<std::uint8_t, 256> data {};
    }; // data=256

    /* ─────────────────────────
   Parameter-change (IPR/IPW)
   ───────────────────────── */
    // TX81Z param-change header uses: F0 43 1n … with group/subgroup/param bytes.
    // You’ll pass exact group/subgroup/param as documented on p.67–75 of the manual.
    struct param_change {
        std::uint8_t group {}; // e.g. 0x04 for VCED/ACED/PCED/Remote (see manual)
        std::uint8_t subgroup {}; // e.g. 0x10, 0x11, 0x03 etc. (varies per table)
        std::uint8_t param {}; // parameter number
        std::uint8_t value {}; // data byte (7-bit)
    };
}

// Parameter change (one parameter)
void encode(std::vector<std::uint8_t>& out, device_id dev, const param_change& pc);

// Bulk set (device receives and loads)
void encode(std::vector<std::uint8_t>& out, device_id dev, const vced& v);
void encode(std::vector<std::uint8_t>& out, device_id dev, const aced& a);
void encode(std::vector<std::uint8_t>& out, device_id dev, const single_voice& sv); // VCED+ACED
void encode(std::vector<std::uint8_t>& out, device_id dev, const vmem_bank& bank);
void encode(std::vector<std::uint8_t>& out, device_id dev, const pced& perf);
void encode(std::vector<std::uint8_t>& out, device_id dev, const pmem_bank& perfs);
void encode(std::vector<std::uint8_t>& out, device_id dev, const system_block& sys);
void encode(std::vector<std::uint8_t>& out, device_id dev, const program_change_table& pct);
void encode(std::vector<std::uint8_t>& out, device_id dev, const microtune_octave& mco);
void encode(std::vector<std::uint8_t>& out, device_id dev, const microtune_fullkbd& mcf);

// Dump request (ask device to send)
void encode_dump_request_vced(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_vmem(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_vced_aced(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_pced(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_pmem(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_system(std::vector<std::uint8_t>& out, device_id dev);
void encode_dump_request_microtune(std::vector<std::uint8_t>& out, device_id dev, bool fullkbd);

// Decode (parse device replies you captured)
void decode(const std::vector<std::uint8_t>& msg, device_id dev, vced& v);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, aced& a);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, single_voice& sv);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, vmem_bank& bank);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, pced& perf);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, pmem_bank& perfs);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, system_block& sys);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, program_change_table& pct);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, microtune_octave& mco);
void decode(const std::vector<std::uint8_t>& msg, device_id dev, microtune_fullkbd& mcf);
}
