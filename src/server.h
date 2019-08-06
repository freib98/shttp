#pragma once

#include <stdint.h>

enum
{
    SERVER_SUCCESS,
    SERVER_ERROR
};

int _initialize_server(uint16_t port);
int run_server(uint16_t port);
void stop_server();
int get_line(int sock, char* buf, int size);
