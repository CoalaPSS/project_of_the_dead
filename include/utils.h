#pragma once

#include <stdio.h>

#define DEBUG(MSG, ...) fprintf(stderr, "DEBUG %s:%d: " MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ERROR_RETURN(EXIT_CODE, MSG, ...) \
    do { \
        fprintf(stderr, "Error %s:%d: " MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        exit(EXIT_CODE); \
    } while(0)