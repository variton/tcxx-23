
#ifndef INTERVALERR_H
#define INTERVALERR_H

#include <err_utils.h>

namespace math{

enum class IntervalError{
  OutOfScope,
  OutOfScopeOnUpperBound,
  OutOfScopeOnLowerBound,
};

ERR_DEFINE_ERROR_INFO(IntervalError,IntervalErrorInfo);

}

#endif
