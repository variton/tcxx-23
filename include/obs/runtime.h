
#ifndef RUNTIME_H
#define RUNTIME_H

#include <xclock.h>
#include <print>

namespace obs{

#define CLOCK_RUNTIME_MAIN                                        \
    static int clock_runtime_main(                                      \
        int argc, char** argv, obs::s_clock & clock);                    \
                                                                        \
    int main(int argc, char** argv) {                                   \
        if (argc == 1) {                                                \
            std::println("missing argument");                           \
            return EXIT_FAILURE;                                        \
        }                                                               \
                                                                        \
        obs::s_clock clock;                                             \
        return clock_runtime_main(argc, argv, clock);                   \
    }                                                                   \
                                                                        \
    static int clock_runtime_main(                                      \
        int argc, char** argv, [[maybe_unused]] obs::s_clock & clock)


#define MICRO_CLOCK_RUNTIME_MAIN                                        \
    static int clock_runtime_main(                                      \
        int argc, char** argv, obs::micro_c& clock);                    \
                                                                        \
    int main(int argc, char** argv) {                                   \
        if (argc == 1) {                                                \
            std::println("missing argument");                           \
            return EXIT_FAILURE;                                        \
        }                                                               \
                                                                        \
        obs::micro_c clock;                                             \
        return clock_runtime_main(argc, argv, clock);                   \
    }                                                                   \
                                                                        \
    static int clock_runtime_main(                                      \
        int argc, char** argv, [[maybe_unused]] obs::micro_c& clock)


} //namespace obs

#endif // RUNTIME_H
