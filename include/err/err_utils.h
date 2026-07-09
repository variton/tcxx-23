
#ifndef ERR_UTILS_H
#define ERR_UTILS_H

#include <error_info.h>
#include <errty.h>

/**
 * @file err_utils.h
 * @brief Utilities for defining error information types.
 */

/**
 * @brief Defines an error information type alias.
 *
 * Creates an alias for `::err::ErrorInfo<ErrorType>` and verifies at compile
 * time that the resulting type satisfies `::topology::ErrorInfoTy`.
 *
 * @param ErrorType Error type.
 * @param AliasName Alias for the corresponding error information type.
 */
#define ERR_DEFINE_ERROR_INFO(ErrorType, AliasName)                            \
  using AliasName = ::err::ErrorInfo<ErrorType>;                               \
  static_assert(::topology::ErrorInfoTy<AliasName>)

#endif
