#include "file.hpp"
#include "string.hpp"
#include "debug.hpp"

#include <string>
#include <iostream>
#include <fstream>

#if _WIN32
#include <windows.h>
#include <tchar.h>
#define BUFSIZE MAX_PATH
#endif

const char* kp::File::join(const char start[], const char end[]) {
    // This delim should change depending on OS
#ifdef _WIN32
    const char delim = '\\';
#else
    const char delim = '/';
#endif

    char seperator = NULL;
    
    // Ensure the last character of the start is a delim
    const char last = (char)start[strlen(start)];
    if(last != delim) {
        seperator = delim;
    }
    
    // If there is a delim at the begining of the end, remove it
    const char first = (char)end[0];
    if(first == delim) {
        end++; // Skip to the next item in the array
    }
    
    return kp::String::format((char*)"%s%c%s", start, seperator, end);
};

kp::File::File(const char* filename) {
    this->filename = filename;
}

const char* kp::File::wd() {
#if _WIN32
	TCHAR directory[BUFSIZE];
	GetCurrentDirectory(BUFSIZE, directory);

	return "Z:\Development\mandrill\vs\Debug";
#else
    return getwd(NULL);
#endif
}

const char* kp::File::path() {
    return join(wd(), filename);
}

const char* kp::File::read() {
    const char* location = path();
    std::ifstream file(filename);
    
    if(file) {
        std::string contents;
        std::string line;
        
        while (file.good()) {
			std::getline(file, line);
            
            // Append the line and a new line escape char to the string
            contents.append(line);
            contents.append("\n");
        }
        
        return contents.c_str();
    } else {
        kp::error("Failed to open %s", filename);
    }
    
    return NULL;
};
