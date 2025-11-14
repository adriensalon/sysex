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

}