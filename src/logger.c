#include "logger.h"

#include <stdio.h>

// Method Description:
// - Logs debug information in red to the stdout stream
// Arguments:
// - msg: the to be logged message
void log_debug(char* msg)
{
    printf("\x1b[32m[Debug]: %s\x1b[0m\n", msg);
}

// Method Description:
// - Logs a error in red to the stderr stream
// Arguments:
// - msg: the to be logged message
void log_error(char* msg)
{
    fprintf(stderr, "\x1b[31m[Error]: %s\x1b[0m\n", msg);
}
