
#define DOCTEST_CONFIG_IMPLEMENT

#include <doctest/doctest.h>

#include <print>
#include <runtime.h>

TEST_CASE("clock behavior") { CHECK(1 + 1 == 2); }

MILLI_CLOCK_RUNTIME_MAIN {
  clock();
  clock();
  const auto time = clock.elapsed();
  std::println("{} ms", time);
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  return context.run();
}
