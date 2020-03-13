#pragma once

typedef struct SHTTPConfig SHTTPConfig;

struct SHTTPConfig
{
    unsigned short int port;
    int listenfd;
};
