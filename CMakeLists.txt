cmake_minimum_required(VERSION 3.4.3)
project(shttp)

set(SOURCES
    main.c
    server.c
    logger.c
)

set(HEADERS
    server.h
    logger.h
)

add_executable(shttp ${SOURCES} ${HEADERS})
