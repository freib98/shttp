#include "server.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Method Description:
// - Prints a help message to the stdout stream and exits the program
void print_help()
{
    printf("Usage: shttp [port]\n");
    printf("\n");
    printf("Options\n");
    printf("-h\x1b[10CDisplay usage\n");
    exit(0);
}

// Method Description:
// - Validates all arguments
// Arguments:
// - argc: the number of arguments
// - argv: pointer to the arguments
int validate_args(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "Usage: %s {portnumber}\n", argv[0]);
        exit(0);
    }

    return 0;
}

// Method Description:
// - Parses the port string to a 16 bit int value. If the value
//      is invalid or the value is greater than a 16 bit int can
//      hold, it throws a error
// Arguments:
// - port_arg: the to be parsed port
uint16_t port_arg_to_uint16(const char* port_arg)
{
    char* port_arg_nptr;
    unsigned long int port = strtoul(port_arg, &port_arg_nptr, 10);

    if (*port_arg_nptr != '\0')
    {
        log_error("Invalid Port");
        exit(0);
    }

    if (port > UINT16_MAX)
    {
        log_error("Port is not in range");
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
