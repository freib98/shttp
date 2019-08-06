cmake_minimum_required(VERSION 3.4.3)
project(shttp)

set(SOURCES
    src/main.c
    src/server.c
    src/logger.c
)

set(HEADERS
    src/server.h
    src/logger.h
)

add_executable(shttp ${SOURCES} ${HEADERS})
