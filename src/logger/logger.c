#include "logger.h"

// TODO: temp
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 init_logger(void) {
    // TODO: create log file
    return true;
}
void end_logger(void) {
    // TODO: cleanup logging/write queued entries
}

void log_output(log_level level, const char *message, ...) {
    const char *level_strings[6] = {"[TRACE]: ", "[DEBUG]: ", "[INFO]: ", "[WARNING]: ", "[ERROR]: ", "[FATAL]: "};
    b8 is_error = level >= LOG_ERROR;
    char out_message[32000];
    memset(out_message, 0, 32000);

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    // TODO: write to log file
    printf("%s%s\n", level_strings[level], out_message);
}