#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *buffer1;
    char *buffer2;
    cmsFloat64Number result;

    // Ensure size is sufficient to split into two non-null strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for strings
    buffer1 = (char *)malloc(size / 2 + 1);
    buffer2 = (char *)malloc(size / 2 + 1);

    if (!buffer1 || !buffer2) {
        free(buffer1);
        free(buffer2);
        return 0;
    }

    // Copy data into strings and null-terminate them
    memcpy(buffer1, data, size / 2);
    buffer1[size / 2] = '\0';
    memcpy(buffer2, data + size / 2, size / 2);
    buffer2[size / 2] = '\0';

    // Initialize a cmsHANDLE for testing
    handle = cmsIT8Alloc(NULL);
    if (!handle) {
        free(buffer1);
        free(buffer2);
        return 0;
    }

    // Call the function-under-test
    result = cmsIT8GetDataDbl(handle, buffer1, buffer2);

    // Clean up
    cmsIT8Free(handle);
    free(buffer1);
    free(buffer2);

    return 0;
}