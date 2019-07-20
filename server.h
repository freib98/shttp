#pragma once

#include <stdint.h>

void initialize_server(uint16_t port);

void run_server(uint16_t port);

void stop_server();
