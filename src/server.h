#pragma once

#include <stdint.h>

typedef enum
{
    SERVER_SUCCESS,
    SERVER_ERROR
} server_error;

int run_server(uint16_t port);
static int initialize_server(uint16_t port);
void stop_server();
