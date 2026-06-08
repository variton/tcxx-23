
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <policies.h>

template <math::IntervalBoundType BoundType>
using ClosedInterval =
    math::BasicInterval<BoundType, math::ClosedIntervalPolicy<BoundType>>;

template <math::IntervalBoundType BoundType>
using OpenInterval =
    math::BasicInterval<BoundType, math::OpenIntervalPolicy<BoundType>>;

template <math::IntervalBoundType BoundType>
using HalfClosedLowerBound =
    math::BasicInterval<BoundType, math::HalfClosedLowerBoundPolicy<BoundType>>;

template <math::IntervalBoundType BoundType>
using HalfClosedUpperBound =
    math::BasicInterval<BoundType, math::HalfClosedUpperBoundPolicy<BoundType>>;

TEST_CASE("ClosedInterval contains values inside [lower, upper]") {

  ClosedInterval<int> interval{1, 10};

  CHECK(interval.has(1).has_value());
  CHECK(interval.has(5).has_value());
  CHECK(interval.has(10).has_value());
}

TEST_CASE("ClosedInterval rejects values outside [lower, upper]") {
  ClosedInterval<int> interval{1, 10};

  auto below = interval.has(0);
  REQUIRE_FALSE(below.has_value());
  CHECK(below.error().type == math::IntervalError::OutOfScopeOnLowerBound);

  auto above = interval.has(11);
  REQUIRE_FALSE(above.has_value());
  CHECK(above.error().type == math::IntervalError::OutOfScopeOnUpperBound);
}

TEST_CASE("OpenInterval has values inside (lower, upper)") {
  OpenInterval<int> interval{1, 10};

  CHECK(interval.has(5).has_value());
}

TEST_CASE("OpenInterval rejects lower and upper endpoints") {
  OpenInterval<int> interval{1, 10};

  auto lower = interval.has(1);
  REQUIRE_FALSE(lower.has_value());
  CHECK(lower.error().type == math::IntervalError::OutOfScopeOnLowerBound);
  CHECK(lower.error().message ==
        "value is outside the open interval at the lower bound");

  auto upper = interval.has(10);
  REQUIRE_FALSE(upper.has_value());
  CHECK(upper.error().type == math::IntervalError::OutOfScopeOnUpperBound);
  CHECK(upper.error().message ==
        "value is outside the open interval at the upper bound");
}

TEST_CASE("OpenInterval rejects values outside (lower, upper)") {
  OpenInterval<int> interval{1, 10};

  auto below = interval.has(0);
  REQUIRE_FALSE(below.has_value());
  CHECK(below.error().type == math::IntervalError::OutOfScopeOnLowerBound);

  auto above = interval.has(11);
  REQUIRE_FALSE(above.has_value());
  CHECK(above.error().type == math::IntervalError::OutOfScopeOnUpperBound);
}

TEST_CASE("HalfClosedUpperBound has values inside (lower, upper]") {
  HalfClosedUpperBound<int> interval{1, 10};

  CHECK(interval.has(5).has_value());
  CHECK(interval.has(10).has_value());
}

TEST_CASE("HalfClosedUpperBound rejects lower endpoint and below") {
  HalfClosedUpperBound<int> interval{1, 10};

  auto lower = interval.has(1);
  REQUIRE_FALSE(lower.has_value());
  CHECK(lower.error().type == math::IntervalError::OutOfScopeOnLowerBound);

  auto below = interval.has(0);
  REQUIRE_FALSE(below.has_value());
  CHECK(below.error().type == math::IntervalError::OutOfScopeOnLowerBound);
}

TEST_CASE("HalfClosedUpperBound rejects values above upper bound") {
  HalfClosedUpperBound<int> interval{1, 10};

  auto above = interval.has(11);
  REQUIRE_FALSE(above.has_value());
  CHECK(above.error().type == math::IntervalError::OutOfScopeOnUpperBound);
}

TEST_CASE("HalfClosedLowerBound has values inside [lower, upper)") {
  HalfClosedLowerBound<int> interval{1, 10};

  CHECK(interval.has(1).has_value());
  CHECK(interval.has(5).has_value());
}

TEST_CASE("HalfClosedLowerBound rejects upper endpoint and above") {
  HalfClosedLowerBound<int> interval{1, 10};

  auto upper = interval.has(10);
  REQUIRE_FALSE(upper.has_value());
  CHECK(upper.error().type == math::IntervalError::OutOfScopeOnUpperBound);

  auto above = interval.has(11);
  REQUIRE_FALSE(above.has_value());
  CHECK(above.error().type == math::IntervalError::OutOfScopeOnUpperBound);
}

TEST_CASE("HalfClosedLowerBound rejects values below lower bound") {
  HalfClosedLowerBound<int> interval{1, 10};

  auto below = interval.has(0);
  REQUIRE_FALSE(below.has_value());
  CHECK(below.error().type == math::IntervalError::OutOfScopeOnLowerBound);
}

TEST_CASE("Intervals work with floating point bounds") {
  ClosedInterval<double> closed{1.5, 10.5};
  OpenInterval<double> open{1.5, 10.5};
  HalfClosedLowerBound<double> lower{1.5, 10.5};
  HalfClosedUpperBound<double> upper{1.5, 10.5};

  CHECK(closed.has(1.5).has_value());
  CHECK(closed.has(10.5).has_value());

  CHECK_FALSE(open.has(1.5).has_value());
  CHECK_FALSE(open.has(10.5).has_value());
  CHECK(open.has(5.0).has_value());

  CHECK(lower.has(1.5).has_value());
  CHECK_FALSE(lower.has(10.5).has_value());

  CHECK_FALSE(upper.has(1.5).has_value());
  CHECK(upper.has(10.5).has_value());
}
