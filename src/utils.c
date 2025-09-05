#include "../include/utils.h"


void DEBUG(char *msg) {
    debug_count++;
    printf("DEBUG %d %s\n", debug_count, msg);
}

void throw_exception(char *msg) {
    printf("%s\n", msg);
    exit(1);
}