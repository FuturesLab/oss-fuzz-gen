#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_469(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    void *buffer;
    cmsUInt32Number bufferSize;
    cmsBool result;

    // Initialize the handle with some valid data
    handle = cmsIT8Alloc(NULL);
    if (!handle) {
        return 0;
    }

    // Allocate a buffer with a size of at least 1 to avoid NULL
    buffer = malloc(size > 0 ? size : 1);
    if (!buffer) {
        cmsIT8Free(handle);
        return 0;
    }

    // Initialize bufferSize with a non-zero value
    bufferSize = (cmsUInt32Number)(size > 0 ? size : 1);

    // Call the function-under-test
    result = cmsIT8SaveToMem(handle, buffer, &bufferSize);

    // Free the allocated resources
    free(buffer);
    cmsIT8Free(handle);

    return 0;
}