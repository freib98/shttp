#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help()
{
    fprintf(stdout, "Usage: shttp [port]\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Options\n");
    fprintf(stdout, "-h\x1b[10CDisplay usage\n");
    exit(0);
}

int validate_args(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s {portnumber}\n", argv[0]);
        exit(0);
    }

    return 0;
}

uint16_t port_arg_to_uint16(const char* port_arg)
{
    char* port_arg_nptr;
    unsigned long int port = strtoul(port_arg, &port_arg_nptr, 10);

    if (*port_arg_nptr != '\0')
    {
        printf("Invalid Port");
        exit(0);
    }

    if (port > UINT16_MAX)
    {
        printf("Port is not in range");
        exit(0);
    }

    return (uint16_t)port;
}

int main(int argc, char** argv)
{
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        print_help();
    }

    validate_args(argc, argv);

    run_server(port_arg_to_uint16(argv[1]));
}
