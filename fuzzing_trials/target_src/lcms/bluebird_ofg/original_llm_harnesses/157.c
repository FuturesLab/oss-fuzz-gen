#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char filename[256];

    // Initialize the handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure filename is a valid C-string and not NULL
    if (size > 0 && size < sizeof(filename)) {
        memcpy(filename, data, size);
        filename[size] = '\0'; // Null-terminate to ensure it's a valid string
    } else {
        strncpy(filename, "default_filename.txt", sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SaveToFile(handle, filename);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}