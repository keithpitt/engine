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
    // Append the resources directory to the search paths if we're on an
    // OSX.
    const char* directory = kp::string::format("%s/%s", PHYSFS_getBaseDir(), "Contents/Resources");

    if(PHYSFS_mount(directory, NULL, 1) == 0)
    {
        kp::error("PHYSFS_mount(%c): %s", directory, PHYSFS_getLastError());
    }
#endif
};

void kp::file::cleanup()
{
    if(PHYSFS_deinit() == 0)
    {
        kp::error("PHYSFS_deinit: %s", PHYSFS_getLastError());
    }
}

const char* kp::file::read(const char filename[])
{
    PHYSFS_File* handle = PHYSFS_openRead(filename);

    if(handle == NULL)
    {
        kp::error("PHYSFS_openRead(%s): %s", filename, PHYSFS_getLastError());
    }

    // Create a buffer big enough for the file
    PHYSFS_sint64 size = PHYSFS_fileLength(handle);
    char buffer[size];

    // Read the bytes
    if(PHYSFS_readBytes(handle, buffer, size) != size) {
        kp::error("PHYSFS_readBytes(%s): %s", filename, PHYSFS_getLastError());
    }

    // Close the file handle
    PHYSFS_close(handle);

    std::string result = std::string(buffer, (size_t) size);

    return result.c_str();
}
