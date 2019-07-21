#include "server.h"

#include "logger.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

void _initialize_server(uint16_t port)
{
    struct sockaddr_in connection_socket_addr;
    memset(&connection_socket_addr, 0, sizeof(connection_socket_addr));
    connection_socket_addr.sin_family = AF_INET;
    connection_socket_addr.sin_port = htons(port);
    connection_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        log_error("Could not create listen socket");
    }

    if (bind(listenfd, (struct sockaddr*)&connection_socket_addr, sizeof(connection_socket_addr)) == -1)
    {
        log_error("Could not bind socket to port");
    }
}

void run_server(uint16_t port)
{
    _initialize_server(port);
}

void stop_server()
{
}
