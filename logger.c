#include "logger.h"

#include <stdio.h>

// Method Description:
// - Logs a error in red to the stderr stream
// Arguments:
// - msg: the to be logged message
void log_error(char* msg)
{
    fprintf(stderr, "\x1b[31mError: %s\x1b[0m\n", msg);
}
