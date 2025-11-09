#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <type_traits>

namespace sysex {

template <
    typename Tag,
    typename T,
    T Min = std::numeric_limits<T>::lowest(),
    T Max = std::numeric_limits<T>::max(),
    T DefaultValue = Min>
struct parameter {
    // static_assert(std::is_assignable_v<T, int>, "parameter requires an integral underlying type");
    static_assert(Min <= Max, "parameter: Min must be <= Max");

    using value_type = T;
    static constexpr value_type min_value = Min;
    static constexpr value_type max_value = Max;
    static constexpr value_type default_value = DefaultValue;

    constexpr parameter()
        : _value(DefaultValue)
    {
    }

    // constexpr constructor: throws at runtime; ill-formed if evaluated in constexpr with bad value
    constexpr parameter(T v)
    {
        *this = v;
    }

    constexpr parameter& operator=(T v)
    {
        if (v < Min || v > Max) {
            throw std::out_of_range("parameter: value out of range");
        }
        _value = v;
        return *this;
    }

    // clamped construction (never throws)
    static constexpr parameter from_clamped(T v) noexcept
    {
        return parameter(_clamp(v));
    }

    template <typename RandomDevice = std::mt19937>
    static parameter random(RandomDevice&& rng = RandomDevice { std::random_device {}() })
    {
        if constexpr (std::is_integral_v<T>) {
            static_assert(!std::is_same_v<T, bool>, "parameter::random does not support bool");

            using DistT = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
            // ensure bounds fit in DistT (they should for normal small integer T)
            std::uniform_int_distribution<DistT> dist(
                static_cast<DistT>(Min),
                static_cast<DistT>(Max));
            return parameter(static_cast<T>(dist(rng)));
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(Min, Max);
            return parameter(dist(rng));
        } else {
            static_assert(std::is_arithmetic_v<T>, "parameter::random requires arithmetic T");
        }
    }

    // accessors
    constexpr T value() const noexcept { return _value; }
    explicit constexpr operator T() const noexcept { return _value; }

    // comparisons (only with same named parameter)
    constexpr bool operator==(const parameter& o) const noexcept { return _value == o._value; }
    constexpr bool operator!=(const parameter& o) const noexcept { return _value != o._value; }
    constexpr bool operator<(const parameter& o) const noexcept { return _value < o._value; }
    constexpr bool operator>(const parameter& o) const noexcept { return _value > o._value; }
    constexpr bool operator<=(const parameter& o) const noexcept { return _value <= o._value; }
    constexpr bool operator>=(const parameter& o) const noexcept { return _value >= o._value; }

    // arithmetic (clamped; widen first to avoid UB)
    constexpr parameter operator+(const parameter& o) const noexcept
    {
        using Wide = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
        Wide w = static_cast<Wide>(_value) + static_cast<Wide>(o._value);
        return from_clamped(static_cast<T>(w));
    }
    constexpr parameter operator-(const parameter& o) const noexcept
    {
        using Wide = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
        Wide w = static_cast<Wide>(_value) - static_cast<Wide>(o._value);
        return from_clamped(static_cast<T>(w));
    }
    constexpr parameter& operator+=(const parameter& o) noexcept { return *this = *this + o; }
    constexpr parameter& operator-=(const parameter& o) noexcept { return *this = *this - o; }

    // ++/--
    constexpr parameter& operator++() noexcept { return *this = from_clamped(_value + 1); }
    constexpr parameter operator++(int) noexcept
    {
        parameter tmp(*this);
        ++(*this);
        return tmp;
    }
    constexpr parameter& operator--() noexcept { return *this = from_clamped(_value - 1); }
    constexpr parameter operator--(int) noexcept
    {
        parameter tmp(*this);
        --(*this);
        return tmp;
    }

private:
    T _value;

    static constexpr T _clamp(T v) noexcept
    {
        return v < Min ? Min : (v > Max ? Max : v);
    }
};

}
