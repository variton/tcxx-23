
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <print>
#include <string>
#include <thread>
#include <xclock.h>

using namespace std::chrono_literals;

TEST_CASE("Xclock elasped_to_str init [seconds] OK") {
  obs::Xclock clock;
  CHECK(clock.elapsed_to_str() == "0 s");
}

TEST_CASE("Xclock elasped [milliseconds] OK") {
  obs::milli_c clock;
  clock();
  std::this_thread::sleep_for(10ms);
  clock();
  CHECK(clock.elapsed() >= 10);
}

TEST_CASE("Xclock elasped init [milliseconds] OK") {
  obs::micro_c clock;
  clock();
  std::this_thread::sleep_for(50us);
  clock();
  CHECK(clock.elapsed() >= 50);
}

TEST_CASE("Xclock elasped init [nanoseconds] OK") {
  obs::nano_c clock;
  clock();
  std::this_thread::sleep_for(50ns);
  clock();
  CHECK(clock.elapsed() >= 50);
}
