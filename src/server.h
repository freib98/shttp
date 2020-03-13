#pragma once

#include <stdint.h>

#include "internal.h"

typedef enum
{
    SERVER_SUCCESS,
    SERVER_ERROR
} server_error;

int run_server(SHTTPConfig*);
void stop_server();
