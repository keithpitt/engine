#include "debug.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void kp::debug(const char* message, ...) {
    va_list args;
    
    // `args` is the variable to load the arguments into. the second parameter
    // is the parameter name of the first variable before the ... begins.
    va_start(args, message);
    
    fprintf(stdout, "Debug: ");
    vfprintf(stdout, message, args);
    fprintf(stdout, "\n");
    
    // need to call this because we used va_start
    va_end(args);
}

void kp::error(const char* message, ...) {
    va_list args;
    
    // `args` is the variable to load the arguments into. the second parameter
    // is the parameter name of the first variable before the ... begins.
    va_start(args, message);
    
    fprintf(stderr, "Error: ");
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    
    // need to call this because we used va_start
    va_end(args);
    
    exit(EXIT_FAILURE);
}