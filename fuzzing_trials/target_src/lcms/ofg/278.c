#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "lcms2.h"  // Assuming the library providing cmsIT8GetProperty is Little CMS

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_278(const uint8_t *data, size_t size) {
    // Initialize a cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *propertyName = (char *)malloc(size + 1);
    if (propertyName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyName, data, size);
    propertyName[size] = '\0';

    // Check if the propertyName is a valid IT8 property name
    // For the sake of this example, let's assume a valid property name is alphanumeric
    // and does not exceed a certain length (e.g., 50 characters)
    size_t maxPropertyNameLength = 50;
    size_t actualLength = strnlen(propertyName, maxPropertyNameLength + 1);
    if (actualLength > maxPropertyNameLength || strspn(propertyName, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") != actualLength) {
        free(propertyName);
        cmsIT8Free(handle);
        return 0;
    }

    // Call the function under test
    const char *result = cmsIT8GetProperty(handle, propertyName);

    // Optionally, check the result and perform some operation
    if (result != NULL) {
        // Do something with the result if needed
    }

    // Clean up
    cmsIT8Free(handle);
    free(propertyName);

    return 0;
}

#ifdef __cplusplus
}
#endif