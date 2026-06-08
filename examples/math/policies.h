
#ifndef POLICIES_H
#define POLICIES_H

#include <interval.h>

namespace math{

template <typename BoundType>
struct ClosedIntervalPolicy {
    static std::expected<void, IntervalErrorInfo>
    has(const BoundType& lower,
        const BoundType& upper,
        const BoundType& value) noexcept {
        if (value < lower) {
            return err::unexpected(
                IntervalError::OutOfScopeOnLowerBound,
                "value is below the lower bound of the closed interval"
            );
        }

        if (value > upper) {
            return err::unexpected(
                IntervalError::OutOfScopeOnUpperBound,
                "value is above the upper bound of the closed interval"
            );
        }

        return {};
    }
};

template <typename BoundType>
struct OpenIntervalPolicy {
    static std::expected<void, IntervalErrorInfo>
    has(const BoundType& lower,
        const BoundType& upper,
        const BoundType& value) noexcept {
        if (value <= lower) {
            return err::unexpected(
                   IntervalError::OutOfScopeOnLowerBound,
                   "value is outside the open interval at the lower bound"
            );
        }

        if (value >= upper) {
            return err::unexpected(
                  IntervalError::OutOfScopeOnUpperBound,
                  "value is outside the open interval at the upper bound"
            );
        }

        return {};
    }
};

template <typename BoundType>
struct HalfClosedLowerBoundPolicy {
    static std::expected<void, IntervalErrorInfo>
    has(const BoundType& lower,
        const BoundType& upper,
        const BoundType& value) noexcept {
        if (value < lower) {
            return err::unexpected(
                  IntervalError::OutOfScopeOnLowerBound,
                  "value is below the lower bound of the half-closed-lower interval"
            );
        }

        if (value >= upper) {
            return err::unexpected(
                  IntervalError::OutOfScopeOnUpperBound,
                  "value is outside the upper bound of the half-closed-lower interval"
            );
        }

        return {};
    }
};

template <typename BoundType>
struct HalfClosedUpperBoundPolicy {
    static std::expected<void, IntervalErrorInfo>
    has(const BoundType& lower,
        const BoundType& upper,
        const BoundType& value) noexcept {
        if (value <= lower) {
            return err::unexpected(
                IntervalError::OutOfScopeOnLowerBound,
                "value is outside the lower bound of the half-closed-upper interval"
            );
        }

        if (value > upper) {
            return err::unexpected(
                IntervalError::OutOfScopeOnUpperBound,
                "value is above the upper bound of the half-closed-upper interval"
            );
        }

        return {};
    }
};

}

#endif
