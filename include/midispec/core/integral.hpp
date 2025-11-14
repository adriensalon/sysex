#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace midispec {

/// @brief
/// @tparam T
/// @tparam MinValue
/// @tparam MaxValue
/// @tparam DefaultValue
template <typename T, T MinValue = std::numeric_limits<T>::lowest(), T MaxValue = std::numeric_limits<T>::max(), T DefaultValue = MinValue>
struct integral {

    static_assert(std::is_integral_v<T>, "Requires an integral T underlying type");
    static_assert(MinValue <= MaxValue, "Requires MinValue to be <= MaxValue");

    static constexpr T min_value = MinValue;
    static constexpr T max_value = MaxValue;
    static constexpr T default_value = DefaultValue;

    constexpr integral()
        : _value(DefaultValue)
    {
    }

    constexpr integral(const T value)
    {
        *this = value;
    }

    constexpr integral& operator=(const T value)
    {
#if defined(MIDISPEC_BOUND_CHECK)
        if (value < MinValue || value > MaxValue) {
            throw std::out_of_range(std::string("Requires value in range, here MinValue=") + std::to_string(MinValue) + ", MaxValue=" + std::to_string(MaxValue) + ", Value=" + std::to_string(value));
        }
        _value = value;
#else
        _value = _clamp(value);

#endif
        return *this;
    }

    static constexpr integral from_clamped(const T value) noexcept
    {
        return integral(_clamp(value));
    }

    template <typename RandomDevice = std::mt19937>
    static integral from_random(RandomDevice&& random_device = RandomDevice { std::random_device {}() })
    {
        if constexpr (std::is_integral_v<T>) {
            static_assert(!std::is_same_v<T, bool>, "Requires not bool");
            using WideT = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
            const std::uniform_int_distribution<WideT> _distribution(static_cast<WideT>(MinValue), static_cast<WideT>(MaxValue));
            return integral(_clamp(static_cast<T>(_distribution(random_device))));

        } else if constexpr (std::is_floating_point_v<T>) {
            const std::uniform_real_distribution<T> _distribution(MinValue, MaxValue);
            return integral(_clamp(_distribution(random_device)));

        } else {
            static_assert(std::is_arithmetic_v<T>, "Requires arithmetic T");
        }
    }

    constexpr T value() const noexcept
    {
        return _value;
    }

    explicit constexpr operator T() const noexcept
    {
        return _value;
    }

    constexpr bool operator==(const integral& other) const noexcept
    {
        return _value == other._value;
    }

    constexpr bool operator!=(const integral& other) const noexcept
    {
        return _value != other._value;
    }

    constexpr bool operator<(const integral& other) const noexcept
    {
        return _value < other._value;
    }

    constexpr bool operator>(const integral& other) const noexcept
    {
        return _value > other._value;
    }

    constexpr bool operator<=(const integral& other) const noexcept
    {
        return _value <= other._value;
    }

    constexpr bool operator>=(const integral& other) const noexcept
    {
        return _value >= other._value;
    }

    constexpr integral operator+(const integral& other) const noexcept
    {
        using WideT = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
        const WideT _wide = static_cast<WideT>(_value) + static_cast<WideT>(other._value);
        return from_clamped(static_cast<T>(_wide));
    }

    constexpr integral operator-(const integral& other) const noexcept
    {
        using WideT = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
        WideT _wide = static_cast<WideT>(_value) - static_cast<WideT>(other._value);
        return from_clamped(static_cast<T>(_wide));
    }

    constexpr integral& operator+=(const integral& other) noexcept
    {
        return *this = *this + other;
    }

    constexpr integral& operator-=(const integral& other) noexcept
    {
        return *this = *this - other;
    }

    constexpr integral& operator++() noexcept
    {
        return *this = from_clamped(_value + 1);
    }

    constexpr integral operator++(int) noexcept
    {
        integral tmp(*this);
        ++(*this);
        return tmp;
    }

    constexpr integral& operator--() noexcept
    {
        return *this = from_clamped(_value - 1);
    }

    constexpr integral operator--(int) noexcept
    {
        integral tmp(*this);
        --(*this);
        return tmp;
    }

private:
    T _value;

    static constexpr T _clamp(T value) noexcept
    {
        return value < MinValue ? MinValue : (value > MaxValue ? MaxValue : value);
    }
};

}
