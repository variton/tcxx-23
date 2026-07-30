#ifndef XCLOCK_H
#define XCLOCK_H

#include <chrono>
#include <nc.h>
#include <string>
#include <string_view>

namespace obs {

/**
 * @brief Alias for movable, non-copyable types.
 *
 * @tparam T Type to make movable.
 */
template <typename T> using Movable = core::NC<T>;

/**
 * @brief Simple elapsed-time measurement utility.
 *
 * Starts timing on the first call to operator() and stops/measures on the next
 * call.
 *
 * @tparam CLOCK Clock type used for time measurement.
 * @tparam PRECISION Duration precision used for stored time points.
 */
template <typename CLOCK = std::chrono::system_clock,
          typename PRECISION = std::chrono::seconds>
class Xclock : public Movable<Xclock<CLOCK, PRECISION>> {
public:
  /**
   * @brief Constructs an idle clock.
   */
  Xclock() noexcept;

  /**
   * @brief Destroys the clock.
   */
  ~Xclock();

  /**
   * @brief Toggles the clock between start and stop states.
   */
  void operator()() noexcept;

  /**
   * @brief Returns the last measured elapsed time.
   *
   * @return View of the elapsed-time string.
   */
  std::string_view elapsed_to_str() const noexcept;

  PRECISION elasped() const noexcept;

private:
  /**
   * @brief Starts time measurement.
   */
  void start() noexcept;

  /**
   * @brief Stops time measurement.
   */
  void stop() noexcept;

  /**
   * @brief Updates the elapsed-time string from the stored time points.
   */
  void measure() noexcept;

  bool started_; ///< Indicates whether the clock is currently running.
  std::string str_time_elapsed_; ///< Last measured elapsed time.
  typename PRECISION::rep time_elapsed_; ///
  std::chrono::time_point<CLOCK, PRECISION> begin_; ///< Start time point.
  std::chrono::time_point<CLOCK, PRECISION> end_;   ///< Stop time point.
};

} // namespace obs

#include <xclock.tpp>

#endif // XCLOCK_H
