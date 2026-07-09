
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <thread>
#include <xclock.h>

using namespace std::chrono_literals;

TEST_CASE("Xclock elasped init [seconds] OK") {
  obs::Xclock clock;
  CHECK(clock.elapsed() == "0 s");
}

TEST_CASE("Xclock elasped [seconds] OK") {
  obs::s_clock clock;
  clock();
  std::this_thread::sleep_for(1s);
  clock();
  CHECK(clock.elapsed() == "1 s");
}

TEST_CASE("Xclock elasped [milliseconds] OK") {
  obs::milli_c clock;
  clock();
  std::this_thread::sleep_for(500ms);
  clock();
  CHECK(clock.elapsed() == "500 ms");
}
