#include "logger.h"

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 initialize_logging(){
  // TODO create log file.
  return TRUE;
}

void shutdown_logging(){
  // TODO: cleanup logging/write queued entries/
}

KAPI void log_output(log_level level, const char* message, ...){
  const char* level_strings[6] = {"[FATAl]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
  b8 is_error = level < 2;

  // Impose a 32k character limit on a single log entry.
  char out_message[32000];
  memset(out_message, 0, sizeof(out_message));

  // Handles variadic arguments
  __builtin_va_list arg_ptr;
  va_start(arg_ptr, message);
  // print the formatted message.
  vsnprintf(out_message, 32000, message, arg_ptr);
  va_end(arg_ptr);

  // Prepend the appropriate level string to the output message.
  char prepend_message[32000];
  sprintf(prepend_message, "%s%s\n", level_strings[level], out_message);

  // TODO: platform specific output.
  printf("%s", prepend_message);

}

