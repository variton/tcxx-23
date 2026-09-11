#ifndef RUNTIME_H
#define RUNTIME_H

#include <print>
#include <xclock.h>

namespace obs {

/**
 * @brief Defines a program entry point using an `obs::s_clock`.
 *
 * The resulting function body receives `argc`, `argv`, and `clock`.
 */
#define CLOCK_RUNTIME_MAIN                                                     \
  static int clock_runtime_main(int argc, char **argv, obs::s_clock &clock);   \
                                                                               \
  int main(int argc, char **argv) {                                            \
    if (argc == 1) {                                                           \
      std::println("missing argument");                                        \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
                                                                               \
    obs::s_clock clock;                                                        \
    return clock_runtime_main(argc, argv, clock);                              \
  }                                                                            \
                                                                               \
  static int clock_runtime_main(int argc, char **argv,                         \
                                [[maybe_unused]] obs::s_clock &clock)

/** @brief Defines a program entry point using an `obs::milli_c` clock. */
#define MILLI_CLOCK_RUNTIME_MAIN                                               \
  static int clock_runtime_main(int argc, char **argv, obs::milli_c &clock);   \
                                                                               \
  int main(int argc, char **argv) {                                            \
    if (argc == 1) {                                                           \
      std::println("missing argument");                                        \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
                                                                               \
    obs::milli_c clock;                                                        \
    return clock_runtime_main(argc, argv, clock);                              \
  }                                                                            \
                                                                               \
  static int clock_runtime_main(int argc, char **argv,                         \
                                [[maybe_unused]] obs::milli_c &clock)

/** @brief Defines a program entry point using an `obs::micro_c` clock. */
#define MICRO_CLOCK_RUNTIME_MAIN                                               \
  static int clock_runtime_main(int argc, char **argv, obs::micro_c &clock);   \
                                                                               \
  int main(int argc, char **argv) {                                            \
    if (argc == 1) {                                                           \
      std::println("missing argument");                                        \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
                                                                               \
    obs::micro_c clock;                                                        \
    return clock_runtime_main(argc, argv, clock);                              \
  }                                                                            \
                                                                               \
  static int clock_runtime_main(int argc, char **argv,                         \
                                [[maybe_unused]] obs::micro_c &clock)

/** @brief Defines a program entry point using an `obs::nano_c` clock. */
#define NANO_CLOCK_RUNTIME_MAIN                                                \
  static int clock_runtime_main(int argc, char **argv, obs::nano_c &clock);    \
                                                                               \
  int main(int argc, char **argv) {                                            \
    if (argc == 1) {                                                           \
      std::println("missing argument");                                        \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
                                                                               \
    obs::nano_c clock;                                                         \
    return clock_runtime_main(argc, argv, clock);                              \
  }                                                                            \
                                                                               \
  static int clock_runtime_main(int argc, char **argv,                         \
                                [[maybe_unused]] obs::nano_c &clock)

} // namespace obs

#endif // RUNTIME_H
