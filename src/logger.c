#include "logger.h"

#include <stdio.h>
#include <time.h>

static const char* level_names[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

static const char* level_colors[] = {
    "\x1b[94m",
    "\x1b[36m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[31m",
    "\x1b[35m"
};

// Method Description:
// - Logs a colored message to the stderr stream
// Arguments:
// - level: defines the log level
// - msg: the message logged to the stderr stream
void log_msg(int level, const char* msg, ...)
{
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

    fprintf(stderr, "%s %s[%s]\x1b[0m ", buf, level_colors[level], level_names[level]);

    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
}
