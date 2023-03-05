#pragma once

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release builds.
#if KRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN = 2,
  LOG_LEVEL_INFO = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_TRACE = 5
} log_level;

b8 initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char* message, ...);

// Logs a fatal-level message.
#ifndef KFATAL
#define KFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#endif

// Logs a error-level message.
#ifndef KERROR
#define KERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

// Logs a warning-level-message.
#if LOG_WARN_ENABLED == 1
#define KWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
// does nothing when LOG_WARN_ENABLED != 1
#define KWARN(message, ...)
#endif

// Logs a info-level message.
#if LOG_INFO_ENABLED == 1
#define KINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
// does nothing when LOG_INFO_ENABLED != 1
#define KINFO(message, ...)
#endif

// Logs a debug-level message.
#if LOG_DEBUG_ENABLED == 1
#define KDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
// does nothing when LOG_DEBUG_ENABLED != 1
#define KDEBUG(message, ...)
#endif

// Logs a trace-level message.
#if LOG_TRACE_ENABLED == 1
#define KTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
// does nothing when LOG_TRACE_ENABLED != 1
#define KTRACE(message, ...)
#endif
