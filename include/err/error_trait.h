
#ifndef ERROR_TRAIT_H
#define ERROR_TRAIT_H

#include <ncnm.h>

namespace err {

template <typename T> using Default = core::NCNM<T>;

template <typename T> struct ErrorTrait : public Default<ErrorTrait<T>> {
  using ErrTypeInfo = T;
  using ErrType = typename T::ErrType_;
};

} // namespace err

#endif // ERROR_TRAIT_H
