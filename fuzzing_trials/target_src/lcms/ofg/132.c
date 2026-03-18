#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle;
    char *propertyName;
    char *propertyValue;

    // Create a dummy handle
    handle = cmsIT8Alloc(0);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the input size is sufficient for splitting into two strings
    if (size < 2) {
        cmsIT8Free(handle);
        return 0;
    }

    // Allocate memory for propertyName and propertyValue
    propertyName = (char *)malloc(size / 2 + 1);
    propertyValue = (char *)malloc(size / 2 + 1);

    if (propertyName == NULL || propertyValue == NULL) {
        free(propertyName);
        free(propertyValue);
        cmsIT8Free(handle);
        return 0;
    }

    // Copy data into propertyName and propertyValue
    memcpy(propertyName, data, size / 2);
    propertyName[size / 2] = '\0'; // Null-terminate the string

    memcpy(propertyValue, data + size / 2, size / 2);
    propertyValue[size / 2] = '\0'; // Null-terminate the string

    // Call the function-under-test
    cmsIT8SetPropertyStr(handle, propertyName, propertyValue);

    // Clean up
    free(propertyName);
    free(propertyValue);
    cmsIT8Free(handle);

    return 0;
}