
#ifndef ERROR_TRAIT_H
#define ERROR_TRAIT_H

#include <ncnm.h>

namespace err {

/** Default non-copyable, non-movable base type. */
template <typename T>
using Default = core::NCNM<T>;

/**
 * @brief Provides error-type information.
 * @tparam T Type containing an `ErrType_` member type.
 */
template <typename T>
struct ErrorTrait : public Default<ErrorTrait<T>> {
  using ErrTypeInfo = T;             ///< Error type-information provider.
  using ErrType = typename T::ErrType_; ///< Underlying error type.
};

} // namespace err

#endif // ERROR_TRAIT_H
