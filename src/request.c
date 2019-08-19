#include "request.h"

#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

// Method Description:
// - Receives the request and extracts the method,
//   the url and the http version. The request headers
//   and the body is currently ignored
// Arguments:
// - request: returns the request method, url and
//   the http version
int receive_request(struct request* request, int port)
{
    char buf[1024];
    size_t buf_len = sizeof(buf);
    int len;

    len = get_line(port, buf, buf_len);

    if (len == 0 || strcmp("\n", buf) == 0)
    {
        return INVALID_REQUEST;
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
    sscanf(token, "HTTP/%u.%u", &request->version.major, &request->version.minor);

    log_infof("Request:");
    log_block();

    // Just read the rest of the request
    while (len > 0 && strcmp("\n", buf))
    {
        len = get_line(port, buf, buf_len);
        log_info(buf, len);
    }

    log_block_end();

    return REQUEST_SUCCESS;
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
