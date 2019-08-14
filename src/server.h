#pragma once

#include <stdint.h>

enum server_error
{
    SERVER_SUCCESS,
    SERVER_ERROR,
    SERVER_INVALID_REQUEST
};

enum request_method
{
    UNDEFINED,
    GET
};

struct http_version
{
    int major;
    int minor;
};

struct request
{
    enum request_method method;
    char url[1024];
    struct http_version version;
};

int run_server(uint16_t port);
int initialize_server(uint16_t port);
void stop_server();
int receive_request(struct request* request);
int get_line(int sock, char* buf, int size);
