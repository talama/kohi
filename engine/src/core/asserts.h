#pragma once

#include "defines.h"

// Disable assertions by commenting the line below.
#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() _builtin_trap()
#endif

KAPI void report_assertion_failure(const char *expression, const char *message,
                                   const char *file, i32 line);

#define KASSERT(expr)                                                          \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
    }                                                                          \
  }

#define KASSERT_MSG(expr, message)                                             \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      report_assertion_failure(#expr, message, __FILE__, __LINE__);            \
    }                                                                          \
  }

#ifdef _DEBUG
#define KASSERT_DEBUG(expr)                                                    \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
      debugBreak();                                                            \
    }                                                                          \
  }
#else
#define KAKASSERT_DEBUG(expr) // Does nothing.
#endif

// If assertions are not enabled
#else
#define KASKASSERT(expr)              // Does nothing.
#define KASKASSERT_MSG(expr, message) // Does nothing.
#define KASKASSERT_DEBUG(expr)        // Does nothing.
#endif
