
#ifndef INTERVALTY_H
#define INTERVALTY_H 

#include <concepts>
#include <cstdint>
#include <error_info.h>

namespace math {

template <typename T>
concept IntervalBoundType =
       std::same_as<T, short>
    || std::same_as<T, int>
    || std::same_as<T, long>
    || std::same_as<T, float>
    || std::same_as<T, double>
    || std::same_as<T, std::uint8_t>
    || std::same_as<T, std::uint16_t>
    || std::same_as<T, std::uint32_t>
    || std::same_as<T, std::uint64_t>;

template <typename Policy, typename BoundType>
concept IntervalPolicy =
    IntervalBoundType<BoundType> &&
    requires(const BoundType& lower,
             const BoundType& upper,
             const BoundType& value) {
        { Policy::has(lower, upper, value) }
            -> std::same_as<std::expected<void, IntervalErrorInfo>>;
    };

}

#endif
