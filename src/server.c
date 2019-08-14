#include "server.h"

#include "logger.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int listenfd;
int connfd;

// Method Description:
// - This is the main routine of the server. It initializes the
//   socket, listens for connections, accepts them and sends
//   a response
// Arguments:
// - port: the port the socket is listening on
int run_server(uint16_t port)
{
    if (initialize_server(port) == SERVER_ERROR)
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

        log_debug("Listening for connections...");
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
            struct request request;
            receive_request(&request);

            char response[1024];

            if (request.http_major_version == 1 && request.http_minor_version == 0)
            {
                if (request.method == GET)
                {
                    strcpy(response, "HTTP/1.0 200 OK\r\nServer: shttp\r\nContent-Type: text/html\r\n\r\nHello World!");
                }
                else
                {
                    strcpy(response, "HTTP/1.0 501 Not Implemented\r\nServer: shttp\r\nContent-Type: text/html\r\n\r\nThe method is not implemented");
                }
            }
            else
            {
                strcpy(response, "HTTP/1.0 505 HTTP Version not supported\r\nServer: shttp\r\nContent-Type: text/html\r\n\r\nThis http server just allows http 1.0 requests");
            }

            log_debug("Sending response:\n%s", response);
            send(connfd, response, strlen(response), 0);

            // Close connection socket
            if (close(connfd) == -1)
            {
                log_error("Could not close the connection socket");
            }
            connfd = 0;

            log_debug("Closed connection");

            exit(0);
            break;
        }

        default:
            if (close(connfd) == -1)
            {
                log_error("Could not close the connection socket");
            }
            connfd = 0;

            break;
        }
    }
}

// Method Description:
// - Creating and configurating the socket
// Arguments:
// - port: the port to configure the socket
int initialize_server(uint16_t port)
{
    struct sockaddr_in connection_socket_addr;
    memset(&connection_socket_addr, 0, sizeof(connection_socket_addr));
    connection_socket_addr.sin_family = AF_INET;
    connection_socket_addr.sin_port = htons(port);
    connection_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    log_debug("Creating the listening socket");
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
    log_debug("The server is listening on port %u", port);

    return SERVER_SUCCESS;
}

// Method Description:
// - Closing all active sockets.
void stop_server()
{
    if (listenfd != 0)
    {
        if (close(listenfd) == -1)
        {
            log_error("Could not close the listening socket");
        }
        connfd = 0;

        log_debug("Closed the listening socket");
    }

    if (connfd != 0)
    {
        if (close(connfd) == -1)
        {
            log_error("Could not close the connection socket");
        }
        connfd = 0;

        log_debug("Closed the connection socket");
    }
}

int receive_request(struct request* request)
{
    char buf[1024];
    size_t buf_len = sizeof(buf);
    int len;

    len = get_line(connfd, buf, buf_len);

    if (len == 0 || strcmp("\n", buf) == 0)
    {
        return SERVER_INVALID_REQUEST;
    }

    // Method
    char* token = strtok(buf, " ");
    if (!strcmp(token, "GET"))
    {
        request->method = GET;
    }
    else
    {
        request->method = UNDEFINED;
    }

    // URL
    token = strtok(NULL, " ");
    strncpy(request->url, token, sizeof(request->url));

    // HTTP VERSION
    token = strtok(NULL, " ");
    sscanf(token, "HTTP/%u.%u", &request->http_major_version, &request->http_minor_version);

    // Just read the rest of the request
    while (len > 0 && strcmp("\n", buf))
    {
        len = get_line(connfd, buf, buf_len);
        log_debug(buf);
    }

    return SERVER_SUCCESS;
}

// Method Description:
// - Reads a line from the socket and returns it as zero
//   terminated string.
// Arguments:
// - sock: the socket where the messages are receved from
// - buf: a pointer the the zero terminated result
// - size: the size of the zero terminated result
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
