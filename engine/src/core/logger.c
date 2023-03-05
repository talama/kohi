#include "logger.h"
#include "assert.h"
#include "platform/platform.h"

// TODO: temporary
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

b8 initialize_logging() {
    // TODO create log file.
    return TRUE;
}

void shutdown_logging() {
    // TODO: cleanup logging/write queued entries/
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATAl]: ", "[ERROR]: ", "[WARN]: ",
                                    "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN;

    // Impose a 32k character limit on a single log entry.
    const i32 msg_length = 32000;
    char out_message[msg_length];
    memset(out_message, 0, sizeof(out_message));

    // Handles variadic arguments
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    // print the formatted message.
    vsnprintf(out_message, msg_length, message, arg_ptr);
    va_end(arg_ptr);

    // Prepend the appropriate level string to the output message.
    char prepend_message[msg_length];
    sprintf(prepend_message, "%s%s\n", level_strings[level], out_message);

    // Platform-specific output.
    if (is_error) {
        platform_console_write_error(prepend_message, level);
    } else {
        platform_console_write(prepend_message, level);
    }
}

void report_assertion_failure(const char* expression, const char* message,
                              const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL,
               "Assertion failure: %s, message: '%s', in file %s, line %d\n",
               expression, message, file, line);
}
