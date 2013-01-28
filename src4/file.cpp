#include "file.hpp"
#include "string.hpp"
#include "debug.hpp"

#include <stdio.h>
#include <string>
#include <physfs/physfs.h>

void kp::file::init(const char* argv0)
{
    if(PHYSFS_init(argv0) == 0)
    {
        kp::error("PHYSFS_init: %s", PHYSFS_getLastError());
    }

#ifdef __APPLE__
    const char* directory = kp::string::format("%s/%s", PHYSFS_getBaseDir(), "Contents/Resources");
#else
    const char* directory = PHYSFS_getBaseDir();
#endif

    if(PHYSFS_mount(directory, NULL, 1) == 0)
    {
        kp::error("PHYSFS_mount(%c): %s", directory, PHYSFS_getLastError());
    }
};

void kp::file::cleanup()
{
    if(PHYSFS_deinit() == 0)
    {
        kp::error("PHYSFS_deinit: %s", PHYSFS_getLastError());
    }
}

const char* kp::file::read(const char* filename)
{
    PHYSFS_File* handle = PHYSFS_openRead(filename);

    if(handle == NULL)
    {
        kp::error("PHYSFS_openRead(%s): %s", filename, PHYSFS_getLastError());
    }

    // Create a buffer big enough for the file
    PHYSFS_sint64 size = PHYSFS_fileLength(handle);

    // Append an extra byte to the string so we can null terminate it
    char* buffer = new char[size+1];

    // Read the bytes
    if(PHYSFS_readBytes(handle, buffer, size) != size)
    {
        kp::error("PHYSFS_read: %s", PHYSFS_getLastError());
    }

    // Null terminate the buffer
    buffer[size] = '\0';

    // Close the file handle
    PHYSFS_close(handle);

    return buffer;
}
