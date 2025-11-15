#pragma once

#include <type_traits>
#include <utility>
#include <vector>

#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief
enum struct capability : std::uint8_t {
    /// @brief Capability can be encoded on the host and received by the hardware
    receive,
    /// @brief Capability can be encoded on the host to make the hardware transmit it
    request,
    /// @brief Capability can be transmitted by the hardware and decoded on the host
    transmit
};

namespace detail {

    // note off

    template <typename T, typename = void>
    struct has_note_off_encode_3 : std::false_type {};

    template <typename T>
    struct has_note_off_encode_3<T, std::void_t<decltype(T::encode_note_off(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_note_off_encode_4 : std::false_type {};

    template <typename T>
    struct has_note_off_encode_4<T, std::void_t<decltype(T::encode_note_off(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint8_t, 0, 127>>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T>
    struct has_note_off_encode : std::bool_constant<has_note_off_encode_3<T>::value || has_note_off_encode_4<T>::value> {};

    template <typename T, typename = void>
    struct has_note_off_decode_3 : std::false_type {};

    template <typename T>
    struct has_note_off_decode_3<T, std::void_t<decltype(T::decode_note_off(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_note_off(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>())), bool>::value> {};

    template <typename T, typename = void>
    struct has_note_off_decode_4 : std::false_type {};

    template <typename T>
    struct has_note_off_decode_4<T, std::void_t<decltype(T::decode_note_off(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_note_off(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>())), bool>::value> {};

    template <typename T>
    struct has_note_off_decode : std::bool_constant<has_note_off_decode_3<T>::value || has_note_off_decode_4<T>::value> {};

    template <capability C, typename T>
    struct has_note_off_capability : std::false_type {};

    template <typename T>
    struct has_note_off_capability<capability::receive, T> : has_note_off_encode<T> {};

    template <typename T>
    struct has_note_off_capability<capability::transmit, T> : has_note_off_decode<T> {};

    // note on

    template <typename T, typename = void>
    struct has_note_on_encode_3 : std::false_type {};

    template <typename T>
    struct has_note_on_encode_3<T, std::void_t<decltype(T::encode_note_on(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_note_on_encode_4 : std::false_type {};

    template <typename T>
    struct has_note_on_encode_4<T, std::void_t<decltype(T::encode_note_on(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint8_t, 0, 127>>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T>
    struct has_note_on_encode : std::bool_constant<has_note_on_encode_3<T>::value || has_note_on_encode_4<T>::value> {};

    template <typename T, typename = void>
    struct has_note_on_decode_3 : std::false_type {};

    template <typename T>
    struct has_note_on_decode_3<T, std::void_t<decltype(T::decode_note_on(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_note_on(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>())), bool>::value> {};

    template <typename T, typename = void>
    struct has_note_on_decode_4 : std::false_type {};

    template <typename T>
    struct has_note_on_decode_4<T, std::void_t<decltype(T::decode_note_on(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_note_on(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>())), bool>::value> {};

    template <typename T>
    struct has_note_on_decode : std::bool_constant<has_note_on_decode_3<T>::value || has_note_on_decode_4<T>::value> {};

    template <capability C, typename T>
    struct has_note_on_capability : std::false_type {};

    template <typename T>
    struct has_note_on_capability<capability::receive, T> : has_note_on_encode<T> {};

    template <typename T>
    struct has_note_on_capability<capability::transmit, T> : has_note_on_decode<T> {};

    // note aftertouch

    template <typename T, typename = void>
    struct has_note_aftertouch_encode : std::false_type {};

    template <typename T>
    struct has_note_aftertouch_encode<T, std::void_t<decltype(T::encode_note_aftertouch(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint8_t, 0, 127>>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_note_aftertouch_decode : std::false_type {};

    template <typename T>
    struct has_note_aftertouch_decode<T, std::void_t<decltype(T::decode_note_aftertouch(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_note_aftertouch(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<integral<std::uint8_t, 0, 127>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_note_aftertouch_capability : std::false_type {};

    template <typename T>
    struct has_note_aftertouch_capability<capability::receive, T> : has_note_aftertouch_encode<T> {};

    template <typename T>
    struct has_note_aftertouch_capability<capability::transmit, T> : has_note_aftertouch_decode<T> {};

    // program change

    template <typename T>
    struct is_program_arg : std::false_type {};

    template <typename U, U Min, U Max>
    struct is_program_arg<integral<U, Min, Max>> : std::bool_constant<std::is_same_v<U, std::uint8_t> && Min == 0> {};

    template <typename Fn>
    struct is_program_change_encode_signature : std::false_type {};

    template <typename Chan, typename Prog>
    struct is_program_change_encode_signature<void (*)(std::vector<std::uint8_t>&, Chan, Prog)> : std::bool_constant<std::is_same_v<Chan, integral<std::uint8_t, 0, 15>> && is_program_arg<Prog>::value> {};

    template <typename Fn>
    struct is_program_change_decode_signature : std::false_type {};

    template <typename Chan, typename Prog>
    struct is_program_change_decode_signature<bool (*)(const std::vector<std::uint8_t>&, Chan&, Prog&)> : std::bool_constant<std::is_same_v<Chan, integral<std::uint8_t, 0, 15>> && is_program_arg<Prog>::value> {};

    template <typename T, typename = void>
    struct has_program_change_decode : std::false_type {};

    template <typename T>
    struct has_program_change_decode<T, std::void_t<decltype(&T::decode_program_change)>> : is_program_change_decode_signature<decltype(&T::decode_program_change)> {};

    template <typename T, typename = void>
    struct has_program_change_encode : std::false_type {};

    template <typename T>
    struct has_program_change_encode<T, std::void_t<decltype(&T::encode_program_change)>> : is_program_change_encode_signature<decltype(&T::encode_program_change)> {};

    template <capability C, typename T>
    struct has_program_change_capability : std::false_type {};

    template <typename T>
    struct has_program_change_capability<capability::receive, T> : detail::has_program_change_encode<T> {};

    template <typename T>
    struct has_program_change_capability<capability::transmit, T> : detail::has_program_change_decode<T> {};

    // pitchbend change

    template <typename T, typename = void>
    struct has_pitchbend_change_encode : std::false_type {};

    template <typename T>
    struct has_pitchbend_change_encode<T, std::void_t<decltype(T::encode_pitchbend_change(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<integral<std::uint16_t, 0, 16383, 8192>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_pitchbend_change_decode : std::false_type {};

    template <typename T>
    struct has_pitchbend_change_decode<T, std::void_t<decltype(T::decode_pitchbend_change(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint16_t, 0, 16383, 8192>&>()))>> : std::bool_constant<std::is_same_v<decltype(T::decode_pitchbend_change(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<integral<std::uint16_t, 0, 16383, 8192>&>())), bool>> {};

    template <capability C, typename T>
    struct has_pitchbend_change_capability : std::false_type {};

    template <typename T>
    struct has_pitchbend_change_capability<capability::receive, T> : has_pitchbend_change_encode<T> {};

    template <typename T>
    struct has_pitchbend_change_capability<capability::transmit, T> : has_pitchbend_change_decode<T> {};

    // clock

    template <typename T, typename = void>
    struct has_clock_encode : std::false_type {};

    template <typename T>
    struct has_clock_encode<T, std::void_t<decltype(T::encode_clock(std::declval<std::vector<std::uint8_t>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_clock_decode : std::false_type {};

    template <typename T>
    struct has_clock_decode<T, std::void_t<decltype(T::decode_clock(std::declval<const std::vector<std::uint8_t>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_clock(std::declval<const std::vector<std::uint8_t>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_clock_capability : std::false_type {};

    template <typename T>
    struct has_clock_capability<capability::receive, T> : has_clock_encode<T> {};

    template <typename T>
    struct has_clock_capability<capability::transmit, T> : has_clock_decode<T> {};

    // song position

    template <typename T, typename = void>
    struct has_song_position_encode : std::false_type {};

    template <typename T>
    struct has_song_position_encode<T, std::void_t<decltype(T::encode_song_position(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint16_t, 0, 16383>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_song_position_decode : std::false_type {};

    template <typename T>
    struct has_song_position_decode<T, std::void_t<decltype(T::decode_song_position(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint16_t, 0, 16383>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_song_position(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint16_t, 0, 16383>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_song_position_capability : std::false_type {};

    template <typename T>
    struct has_song_position_capability<capability::receive, T> : has_song_position_encode<T> {};

    template <typename T>
    struct has_song_position_capability<capability::transmit, T> : has_song_position_decode<T> {};

    // continue

    template <typename T, typename = void>
    struct has_continue_encode : std::false_type {};

    template <typename T>
    struct has_continue_encode<T, std::void_t<decltype(T::encode_continue(std::declval<std::vector<std::uint8_t>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_continue_decode : std::false_type {};

    template <typename T>
    struct has_continue_decode<T, std::void_t<decltype(T::decode_continue(std::declval<const std::vector<std::uint8_t>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_continue(std::declval<const std::vector<std::uint8_t>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_continue_capability : std::false_type {};

    template <typename T>
    struct has_continue_capability<capability::receive, T> : has_continue_encode<T> {};

    template <typename T>
    struct has_continue_capability<capability::transmit, T> : has_continue_decode<T> {};

    // reset

    template <typename T, typename = void>
    struct has_reset_encode : std::false_type {};

    template <typename T>
    struct has_reset_encode<T, std::void_t<decltype(T::encode_reset(std::declval<std::vector<std::uint8_t>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_reset_decode : std::false_type {};

    template <typename T>
    struct has_reset_decode<T, std::void_t<decltype(T::decode_reset(std::declval<const std::vector<std::uint8_t>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_reset(std::declval<const std::vector<std::uint8_t>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_reset_capability : std::false_type {};

    template <typename T>
    struct has_reset_capability<capability::receive, T> : has_reset_encode<T> {};

    template <typename T>
    struct has_reset_capability<capability::transmit, T> : has_reset_decode<T> {};

    // all notes off

    template <typename T, typename = void>
    struct has_all_notes_off_encode : std::false_type {};

    template <typename T>
    struct has_all_notes_off_encode<T, std::void_t<decltype(T::encode_all_notes_off(std::declval<std::vector<std::uint8_t>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_all_notes_off_decode : std::false_type {};

    template <typename T>
    struct has_all_notes_off_decode<T, std::void_t<decltype(T::decode_all_notes_off(std::declval<const std::vector<std::uint8_t>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_all_notes_off(std::declval<const std::vector<std::uint8_t>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_all_notes_off_capability : std::false_type {};

    template <typename T>
    struct has_all_notes_off_capability<capability::receive, T> : has_all_notes_off_encode<T> {};

    template <typename T>
    struct has_all_notes_off_capability<capability::transmit, T> : has_all_notes_off_decode<T> {};

    // activ sens

    template <typename T, typename = void>
    struct has_active_sens_encode : std::false_type {};

    template <typename T>
    struct has_active_sens_encode<T, std::void_t<decltype(T::encode_active_sens(std::declval<std::vector<std::uint8_t>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_active_sens_decode : std::false_type {};

    template <typename T>
    struct has_active_sens_decode<T, std::void_t<decltype(T::decode_active_sens(std::declval<const std::vector<std::uint8_t>&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_active_sens(std::declval<const std::vector<std::uint8_t>&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_active_sens_capability : std::false_type {};

    template <typename T>
    struct has_active_sens_capability<capability::receive, T> : has_active_sens_encode<T> {};

    template <typename T>
    struct has_active_sens_capability<capability::transmit, T> : has_active_sens_decode<T> {};

    // universal inquiry

    template <typename T, typename = void>
    struct has_universal_inquiry_request_encode : std::false_type {};

    template <typename T>
    struct has_universal_inquiry_request_encode<T, std::void_t<decltype(T::encode_universal_inquiry_request(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 127>>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_universal_inquiry_decode : std::false_type {};

    template <typename T>
    struct has_universal_inquiry_decode<T, std::void_t<decltype(T::decode_universal_inquiry(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_universal_inquiry(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 127>&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>(), std::declval<std::uint32_t&>())), bool>::value> {};

    template <capability C, typename T>
    struct has_universal_inquiry_capability : std::false_type {};

    template <typename T>
    struct has_universal_inquiry_capability<capability::request, T> : has_universal_inquiry_request_encode<T> {};

    template <typename T>
    struct has_universal_inquiry_capability<capability::transmit, T> : has_universal_inquiry_decode<T> {};

    // voice patch

    template <typename T, typename = void>
    struct has_voice_patch_encode : std::false_type {};

    template <typename T>
    struct has_voice_patch_encode<T, std::void_t<decltype(T::encode_voice_patch(std::declval<std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>>(), std::declval<const typename T::voice_patch&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_voice_patch_request_encode : std::false_type {};

    template <typename T>
    struct has_voice_patch_request_encode<T, std::void_t<decltype(T::encode_voice_patch_request(std::declval<std::vector<std::uint8_t>&>(), std::declval<const integral<std::uint8_t, 0, 15>&>()))>> : std::true_type {};

    template <typename T, typename = void>
    struct has_voice_patch_decode : std::false_type {};

    template <typename T>
    struct has_voice_patch_decode<T, std::void_t<decltype(T::decode_voice_patch(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<typename T::voice_patch&>()))>> : std::bool_constant<std::is_same<decltype(T::decode_voice_patch(std::declval<const std::vector<std::uint8_t>&>(), std::declval<integral<std::uint8_t, 0, 15>&>(), std::declval<typename T::voice_patch&>())), void>::value> {};

    template <capability C, typename T>
    struct has_voice_patch_capability : std::false_type {};

    template <typename T>
    struct has_voice_patch_capability<capability::receive, T> : has_voice_patch_encode<T> {};

    template <typename T>
    struct has_voice_patch_capability<capability::request, T> : has_voice_patch_request_encode<T> {};

    template <typename T>
    struct has_voice_patch_capability<capability::transmit, T> : has_voice_patch_decode<T> {};
}

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_note_off : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_note_off_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_note_off_v = has_note_off<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_note_on : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_note_on_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_note_on_v = has_note_on<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_note_aftertouch : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_note_aftertouch_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_note_aftertouch_v = has_note_aftertouch<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_program_change : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_program_change_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_program_change_v = has_program_change<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_pitchbend_change : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_pitchbend_change_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_pitchbend_change_v = has_pitchbend_change<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_clock : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_clock_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_clock_v = has_clock<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_song_position : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_song_position_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_song_position_v = has_song_position<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_continue : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_continue_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_continue_v = has_continue<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_reset : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_reset_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_reset_v = has_reset<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_all_notes_off : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_all_notes_off_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_all_notes_off_v = has_all_notes_off<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_active_sens : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_active_sens_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_active_sens_v = has_active_sens<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_universal_inquiry : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_universal_inquiry_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_universal_inquiry_v = has_universal_inquiry<Hardware, Capabilities...>::value;

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
struct has_voice_patch : std::bool_constant<(sizeof...(Capabilities) > 0) && (... && detail::has_voice_patch_capability<Capabilities, Hardware>::value)> {};

/// @brief
/// @tparam Hardware
/// @tparam ...Capabilities
template <typename Hardware, capability... Capabilities>
inline constexpr bool has_voice_patch_v = has_voice_patch<Hardware, Capabilities...>::value;

}