#include "server.h"

#include "logger.h"
#include "request.h"

#include <sys/socket.h>
#include <netinet/in.h>
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
        log_errorf("Could not start listen on socket");
    }

    while (1)
    {
        struct sockaddr client_addr;
        socklen_t client_addr_len;

        log_infof("Listening for connections...");
        if ((connfd = accept(listenfd, &client_addr, &client_addr_len)) == -1)
        {
            log_errorf("Could not accept an incomming connection");
            return SERVER_ERROR;
        }

        switch (fork())
        {
        case -1: // Error while forking
            log_errorf("Could not create a child process for a incomming connection");
            return SERVER_ERROR;

        case 0: // Child process
        {
            struct request request;
            receive_request(&request, connfd);

            char response[1024];

            if (request.version.major == 1 && request.version.major == 0)
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

            log_infof("Sending response:", response);
            log_block();
            log_info(response, strlen(response));
            log_block_end();
            send(connfd, response, strlen(response), 0);

            // Close connection socket
            if (close(connfd) == -1)
            {
                log_errorf("Could not close the connection socket");
            }
            connfd = 0;

            log_infof("Closed connection");

            exit(0);
            break;
        }

        default:
            if (close(connfd) == -1)
            {
                log_errorf("Could not close the connection socket");
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
static int initialize_server(uint16_t port)
{
    struct sockaddr_in connection_socket_addr;
    memset(&connection_socket_addr, 0, sizeof(connection_socket_addr));
    connection_socket_addr.sin_family = AF_INET;
    connection_socket_addr.sin_port = htons(port);
    connection_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    log_infof("Creating the listening socket");
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        log_errorf("Could not create listen socket");
        return SERVER_ERROR;
    }

    if (bind(listenfd, (struct sockaddr*)&connection_socket_addr, sizeof(connection_socket_addr)) == -1)
    {
        log_errorf("Could not bind socket to port");
        return SERVER_ERROR;
    }
    log_infof("The server is listening on port %u", port);

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
            log_errorf("Could not close the listening socket");
        }
        connfd = 0;

        log_infof("Closed the listening socket");
    }

    if (connfd != 0)
    {
        if (close(connfd) == -1)
        {
            log_errorf("Could not close the connection socket");
        }
        connfd = 0;

        log_infof("Closed the connection socket");
    }
}
