#include "file.hpp"
#include "string.hpp"
#include "debug.hpp"

#include <iostream>
#include <fstream>

const char* kp::File::join(const char* start, const char* end) {
    // This delim should change depending on OS
    const char delim = '/';
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

const char* kp::File::path() {
    char* directroy = getwd(NULL);
    
    return join(directroy, filename);
}

const char* kp::File::read() {
    const char* location = path();
    std::ifstream file(location);
    
    if(file) {
        std::string contents;
        std::string line;
        
        while (file.good()) {
            getline(file, line);
            
            // Append the line and a new line escape char to the string
            contents.append(line);
            contents.append("\n");
        }
        
        return contents.c_str();
    } else {
        kp::error("Failed to open %s", location);
    }
    
    return NULL;
};
