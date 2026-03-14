#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_483(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsHANDLE handle;
    char *propertyName;
    char *subPropertyName;
    const char *result;

    // Allocate memory for propertyName and subPropertyName
    propertyName = (char *)malloc(size + 1);
    subPropertyName = (char *)malloc(size + 1);

    // Ensure the allocated memory is not NULL
    if (propertyName == NULL || subPropertyName == NULL) {
        free(propertyName);
        free(subPropertyName);
        return 0;
    }

    // Copy data into propertyName and subPropertyName with null-termination
    memcpy(propertyName, data, size);
    propertyName[size] = '\0';
    memcpy(subPropertyName, data, size);
    subPropertyName[size] = '\0';

    // Create a dummy cmsHANDLE for testing purposes
    handle = cmsIT8Alloc(NULL);

    if (handle != NULL) {
        // Call the function-under-test
        result = cmsIT8GetPropertyMulti(handle, propertyName, subPropertyName);

        // Free the cmsHANDLE
        cmsIT8Free(handle);
    }

    // Free allocated memory
    free(propertyName);
    free(subPropertyName);

    return 0;
}