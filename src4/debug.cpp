#include "debug.hpp"
#include "string.hpp"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

void output(FILE * stream, const char* prefix, const char* format, va_list args)
{
    std::string statement = kp::string::vformat(format, args);
	std::string final = kp::string::format("%s: %s\n", prefix, statement.c_str());

#ifdef _WIN32
    OutputDebugString(final.c_str());
#else
    fprintf(stream, "%s", final.c_str());
#endif
};

void kp::debug::info(const char* message, ...)
{
    va_list args;
    va_start(args, message);

    output(stdout, "Info", message, args);

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
