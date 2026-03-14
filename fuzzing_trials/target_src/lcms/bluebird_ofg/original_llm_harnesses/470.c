#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_470(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    cmsHANDLE handle;
    void *buffer;
    cmsUInt32Number bufferSize;

    // Initialize the handle with a valid IT8 object
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // Return if handle allocation fails
    }

    // Allocate memory for the buffer
    bufferSize = size > 0 ? size : 1; // Ensure bufferSize is not zero
    buffer = malloc(bufferSize);
    if (buffer == NULL) {
        cmsIT8Free(handle);
        return 0; // Return if buffer allocation fails
    }

    // Copy data into the buffer
    memcpy(buffer, data, bufferSize);

    // Call the function-under-test
    cmsIT8SaveToMem(handle, buffer, &bufferSize);

    // Free allocated resources
    free(buffer);
    cmsIT8Free(handle);

    return 0;
}