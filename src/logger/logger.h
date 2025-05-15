#pragma once

#include "types.h"

#define MIN_LOG_LEVEL 2

typedef enum LOG_LEVEL {
    LOG_TRACE       = 0,
    LOG_DEBUG       = 1,
    LOG_INFO        = 2,
    LOG_WARNING     = 3,
    LOG_ERROR       = 4,
    LOG_FATAL       = 5
} log_level;


static const char *level_strings[6] = {"[TRACE]: ", "[DEBUG]: ", "[INFO]: ", "[WARNING]: ", "[ERROR]: ", "[FATAL]: "};

b8 init_logger(void);

void end_logger(void);

// All logging functions converge in log_output
void log_output(log_level level, const char *message, ...);

#define NVKLOG(severity, message, ...) log_output(severity, message, ##__VA_ARGS__);

#define NFATAL(message, ...) log_output(LOG_FATAL, message, ##__VA_ARGS__);

#define NERROR(message, ...) log_output(LOG_ERROR, message, ##__VA_ARGS__);

#if (MIN_LOG_LEVEL <= 3)
    #define NWARNING(message, ...) log_output(LOG_WARNING, message, ##__VA_ARGS__);
#else
    #define NWARNING(message, ...)
#endif

#if (MIN_LOG_LEVEL <= 2)
    #define NINFO(message, ...) log_output(LOG_INFO, message, ##__VA_ARGS__);
#else
    #define NINFO(message, ...)
#endif

#if (MIN_LOG_LEVEL <= 1)
    #define NDEBUG(message, ...) log_output(LOG_DEBUG, message, ##__VA_ARGS__);
#else
    #define NDEBUG(message, ...)
#endif

#if (MIN_LOG_LEVEL == 0)
    #define NTRACE(message, ...) log_output(LOG_TRACE, message, ##__VA_ARGS__);
#else
    #define NTRACE(message, ...)
#endif
