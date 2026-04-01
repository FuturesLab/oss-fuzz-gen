#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Initialize the parameters for cmsIT8SetPropertyStr
    cmsHANDLE handle;
    char *propertyName;
    char *propertyValue;

    // Ensure the data size is sufficient to extract at least two strings
    if (size < 4) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *tempBuffer = (char *)malloc(size + 1);
    if (tempBuffer == NULL) {
        return 0;
    }
    memcpy(tempBuffer, data, size);
    tempBuffer[size] = '\0'; // Null-terminate the buffer

    // Split the buffer into two strings for propertyName and propertyValue
    size_t midPoint = size / 2;
    propertyName = tempBuffer;
    propertyValue = tempBuffer + midPoint;

    // Initialize the handle using cmsIT8Alloc
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        free(tempBuffer);
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SetPropertyStr(handle, propertyName, propertyValue);

    // Clean up
    cmsIT8Free(handle);
    free(tempBuffer);

    return 0;
}