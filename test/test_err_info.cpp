
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <errty.h>
#include <intervalerr.h>

TEST_CASE("IntervalScannerError topology enum class") {
  static_assert(topology::ErrorInfoTy<math::IntervalErrorInfo>);
  CHECK(true);
}
