#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *firstProperty;
    char *secondProperty;
    const char *result;

    if (size < 2) {
        return 0; // Not enough data to proceed
    }

    // Initialize handle (for demonstration purposes, using a dummy handle)
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Allocate and copy data for firstProperty and secondProperty
    firstProperty = (char *)malloc(size / 2 + 1);
    secondProperty = (char *)malloc(size / 2 + 1);

    if (firstProperty == NULL || secondProperty == NULL) {
        cmsIT8Free(handle);
        free(firstProperty);
        free(secondProperty);
        return 0; // Memory allocation failed
    }

    // Copy the first half of the data to firstProperty
    memcpy(firstProperty, data, size / 2);
    firstProperty[size / 2] = '\0'; // Null-terminate

    // Copy the second half of the data to secondProperty
    memcpy(secondProperty, data + size / 2, size / 2);
    secondProperty[size / 2] = '\0'; // Null-terminate

    // Call the function-under-test
    result = cmsIT8GetPropertyMulti(handle, firstProperty, secondProperty);

    // Clean up
    cmsIT8Free(handle);
    free(firstProperty);
    free(secondProperty);

    return 0;
}