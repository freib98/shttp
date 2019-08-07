#include "server.h"

#include "logger.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

int listenfd;
int connfd;

int _initialize_server(uint16_t port)
{
    struct sockaddr_in connection_socket_addr;
    memset(&connection_socket_addr, 0, sizeof(connection_socket_addr));
    connection_socket_addr.sin_family = AF_INET;
    connection_socket_addr.sin_port = htons(port);
    connection_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        log_error("Could not create listen socket");
        return SERVER_ERROR;
    }

    if (bind(listenfd, (struct sockaddr*)&connection_socket_addr, sizeof(connection_socket_addr)) == -1)
    {
        log_error("Could not bind socket to port");
        return SERVER_ERROR;
    }

    return SERVER_SUCCESS;
}

int run_server(uint16_t port)
{
    if (_initialize_server(port) == SERVER_ERROR)
    {
        return SERVER_ERROR;
    }

    if (listen(listenfd, 10) == -1)
    {
        log_error("Could not start listen on socket");
    }

    while (1)
    {
        struct sockaddr client_addr;
        socklen_t client_addr_len;
        if ((connfd = accept(listenfd, &client_addr, &client_addr_len)) == -1)
        {
            log_error("Could not accept an incomming connection");
            return SERVER_ERROR;
        }

        switch (fork())
        {
        case -1: // Error while forking
            log_error("Could not create a child process for a incomming connection");
            return SERVER_ERROR;

        case 0: // Child process
        {
            char buf[1024];
            int len;

            do
            {
                len = get_line(connfd, buf, sizeof(buf));
                printf("%s", buf);
            } while (len > 0 && strcmp("\n", buf));

            char response[1024];
            strcpy(response, "HTTP/1.0 200 OK\r\nServer: shttp\r\nContent-Type: text/html\r\n\r\nHello World!");
            send(connfd, response, strlen(response), 0);

            if (close(connfd) == -1)
            {
                log_error("Could not close the connection socket");
            }

            break;
        }

        default:
            break;
        }
    }
}

void stop_server()
{
}

int get_line(int sock, char* buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';
    return i;
}
