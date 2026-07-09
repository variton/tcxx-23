
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <err_utils.h>
#include <errty.h>
#include <intervalerr.h>

TEST_CASE("IntervalScannerError topology enum class") {
  static_assert(topology::ErrorInfoTy<math::IntervalErrorInfo>);
  CHECK(true);
}

TEST_CASE("DefineErrorInfo macro") {
  enum class ObliviousError {};
  ERR_DEFINE_ERROR_INFO(ObliviousError, ObliviousErrorInfo);
  static_assert(
      std::same_as<ObliviousErrorInfo, err::ErrorInfo<ObliviousError>>);
  CHECK(true);
}
