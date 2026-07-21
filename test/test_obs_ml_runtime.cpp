
#define DOCTEST_CONFIG_IMPLEMENT

#include <doctest/doctest.h>

#include <runtime.h>
#include <print>

TEST_CASE("clock behavior")
{
    CHECK(1 + 1 == 2);
}

MILLI_CLOCK_RUNTIME_MAIN
{
    clock();
    clock();
    //todo change the interface used to extract the elapsed time
    const auto time = clock.elapsed();
    std::println("{}",time);
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run();
}
