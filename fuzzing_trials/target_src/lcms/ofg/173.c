#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free
#include <lcms2.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle;
    const char *propertyName;
    const char *propertyValue;

    // Ensure that size is sufficient to split into two strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the propertyName and propertyValue
    size_t mid = size / 2;
    propertyName = (const char *)malloc(mid + 1);
    propertyValue = (const char *)malloc(size - mid + 1);

    // Copy data into propertyName and propertyValue
    memcpy((void *)propertyName, data, mid);
    memcpy((void *)propertyValue, data + mid, size - mid);

    // Null-terminate the strings
    ((char *)propertyName)[mid] = '\0';
    ((char *)propertyValue)[size - mid] = '\0';

    // Create a cmsIT8 object to use as handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        free((void *)propertyName);
        free((void *)propertyValue);
        return 0;
    }

    // Call the function-under-test
    cmsIT8SetPropertyUncooked(handle, propertyName, propertyValue);

    // Clean up
    cmsIT8Free(handle);
    free((void *)propertyName);
    free((void *)propertyValue);

    return 0;
}