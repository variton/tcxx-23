
#ifndef INTERVALERR_H
#define INTERVALERR_H

#include <error_info.h>

namespace math{

enum class IntervalError{
  OutOfScope,
  OutOfScopeOnUpperBound,
  OutOfScopeOnLowerBound,
};

using IntervalErrorInfo = err::ErrorInfo<IntervalError>;

}

#endif
