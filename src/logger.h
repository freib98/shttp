#pragma once

enum
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

#define log_trace(...) log_msg(LOG_TRACE, __VA_ARGS__)
#define log_debug(...) log_msg(LOG_DEBUG, __VA_ARGS__)
#define log_info(...)  log_msg(LOG_INFO, __VA_ARGS__)
#define log_warn(...)  log_msg(LOG_WARN, __VA_ARGS__)
#define log_error(...) log_msg(LOG_ERROR, __VA_ARGS__)
#define log_fatal(...) log_msg(LOG_FATAL, __VA_ARGS__)

void log_msg(int level, const char* msg, ...);
