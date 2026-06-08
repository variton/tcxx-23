
#ifndef INTERVAL_H
#define INTERVAL_H

#include <ncnm.h>
#include <intervalerr.h>
#include <intervalty.h>
#include <expected>

namespace math{

template <typename T> using Default = core::NCNM<T>;

template <IntervalBoundType BoundType>
class Interval : public Default<Interval<BoundType>>{
public:
    explicit Interval(BoundType lower_bound,
                      BoundType upper_bound) noexcept
        : lower_bound_{lower_bound},
          upper_bound_{upper_bound} {}

    const BoundType& lower_bound() const noexcept {
        return lower_bound_;
    }

    const BoundType& upper_bound() const noexcept {
        return upper_bound_;
    }

private:
    BoundType lower_bound_;
    BoundType upper_bound_;
};

template <typename BoundType, typename Policy>
    requires IntervalPolicy<Policy, BoundType>
class BasicInterval : public Interval<BoundType> {
private:
    using Root = Interval<BoundType>;

public:
    explicit BasicInterval(BoundType lower_bound,
                           BoundType upper_bound) noexcept
        : Root{lower_bound, upper_bound} {}

    std::expected<void, IntervalErrorInfo>
    has(const BoundType& value) const noexcept {
        return Policy::has(
            this->lower_bound(),
            this->upper_bound(),
            value
        );
    }
};

}

#endif
