#include "logger.h"

#include <stdio.h>

void log_error(char* msg)
{
    fprintf(stderr, "\x1b[31mError: %s\x1b[0m\n", msg);
}
