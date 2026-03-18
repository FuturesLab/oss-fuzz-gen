#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h" // Assuming this is the correct header for cmsIT8GetProperty

// Remove 'extern "C"' since this is C code, not C++
int LLVMFuzzerTestOneInput_277(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char propertyName[256]; // Assuming a reasonable size for property name

    if (size < 1) {
        return 0;
    }

    // Initialize handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Copy data to propertyName ensuring it is null-terminated
    size_t copySize = size < sizeof(propertyName) ? size : sizeof(propertyName) - 1;
    memcpy(propertyName, data, copySize);
    propertyName[copySize] = '\0';

    // Call the function-under-test
    const char *result = cmsIT8GetProperty(handle, propertyName);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}