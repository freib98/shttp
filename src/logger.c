#include "logger.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static struct
{
    int block;
} logger;

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

void log_block()
{
    logger.block = 1;
}

void log_block_end()
{
    printf("\n");

    logger.block = 0;
}

void log_msg(int level, const char* msg, int size)
{
    if (!logger.block)
    {
        _log_time_level(level);
    }

    for (int i = 0; i < size; i++)
    {
        switch (msg[i])
        {
        case '\0':
            fprintf(stderr, "\\0");
            break;
        case '\r':
            fprintf(stderr, "\\r");
            break;
        case '\n':
            fprintf(stderr, "\\n");
            break;
        default:
            if (isprint(msg[i]))
                fprintf(stderr, "%c", msg[i]); // Printable character, print it as usual
            else
                fprintf(stderr, "\\x%02x", msg[i]); // Non-printable character, print as hex value

            break;
        }
    }

    if (!logger.block)
    {
        fprintf(stderr, "\n");
    }

    fflush(stderr);
}

// Method Description:
// - Logs a colored message to the stderr stream
// Arguments:
// - level: defines the log level
// - msg: the message logged to the stderr stream
void log_msgf(int level, const char* msg, ...)
{
    if (!logger.block)
    {
        _log_time_level(level);
    }

    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    if (!logger.block)
    {
        fprintf(stderr, "\n");
    }

    fflush(stderr);
}

void _log_time_level(int level)
{
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

    fprintf(stderr, "%s %s[%s]\x1b[0m ", buf, level_colors[level], level_names[level]);
}
