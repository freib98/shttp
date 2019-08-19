#pragma once

typedef enum
{
    REQUEST_SUCCESS,
    INVALID_REQUEST
} request_error;

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

int receive_request(struct request* request, int port);
int get_line(int sock, char* buf, int size);
