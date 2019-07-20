cmake_minimum_required(VERSION 3.4.3)
project(shttp)

set(SOURCES
    main.c
    server.c
)

set(HEADERS
    server.h
)

add_executable(shttp ${SOURCES} ${HEADERS})
