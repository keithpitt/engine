#include "debug.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void output(FILE * stream, const char* prefix, const char* message, va_list args)
{
    fprintf(stdout, "%s: ", prefix);
    vfprintf(stdout, message, args);
    fprintf(stdout, "\n");
};

void kp::debug::info(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    
    output(stdout, "Debug", message, args);
    
    va_end(args);
}

void kp::debug::error(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    
    output(stderr, "Error", message, args);
    va_end(args);
}

void kp::debug::fatal(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    
    output(stdout, "Fatal", message, args);
    
    va_end(args);
    
    exit(EXIT_FAILURE);
}