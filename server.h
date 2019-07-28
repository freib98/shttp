#pragma once

#include <stdint.h>

void _initialize_server(uint16_t port);

void run_server(uint16_t port);

void stop_server();

int get_line(int sock, char* buf, int size);
