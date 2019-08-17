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

#define log_trace(msg, size) log_msg(LOG_TRACE, msg, size)
#define log_debug(msg, size) log_msg(LOG_DEBUG, msg, size)
#define log_info(msg, size)  log_msg(LOG_INFO, msg, size)
#define log_warn(msg, size)  log_msg(LOG_WARN, msg, size)
#define log_error(msg, size) log_msg(LOG_ERROR, msg, size)
#define log_fatal(msg, size) log_msg(LOG_FATAL, msg, size)

#define log_tracef(...) log_msgf(LOG_TRACE, __VA_ARGS__)
#define log_debugf(...) log_msgf(LOG_DEBUG, __VA_ARGS__)
#define log_infof(...)  log_msgf(LOG_INFO, __VA_ARGS__)
#define log_warnf(...)  log_msgf(LOG_WARN, __VA_ARGS__)
#define log_errorf(...) log_msgf(LOG_ERROR, __VA_ARGS__)
#define log_fatalf(...) log_msgf(LOG_FATAL, __VA_ARGS__)

void log_msg(int level, const char* msg, int size);
void log_msgf(int level, const char* msg, ...);

void log_block();
void log_block_end();

void _log_time_level(int level);