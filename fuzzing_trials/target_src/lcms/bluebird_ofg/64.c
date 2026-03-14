#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char filename[256];

    // Initialize handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the filename is null-terminated and not empty
    if (size < 1) {
        cmsIT8Free(handle);
        return 0;
    }

    size_t filename_size = size < sizeof(filename) ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_size);
    filename[filename_size] = '\0';

    // Call the function-under-test
    cmsIT8SaveToFile(handle, filename);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}