#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHANDLE handle;
    char *propertyName;
    cmsUInt32Number value;

    // Ensure size is sufficient for extracting the necessary values
    if (size < sizeof(cmsUInt32Number) + 1) {
        return 0;
    }

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract a string for propertyName from the data
    propertyName = (char *)malloc(size - sizeof(cmsUInt32Number) + 1);
    if (propertyName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyName, data, size - sizeof(cmsUInt32Number));
    propertyName[size - sizeof(cmsUInt32Number)] = '\0'; // Null-terminate the string

    // Extract cmsUInt32Number value from the data
    memcpy(&value, data + size - sizeof(cmsUInt32Number), sizeof(cmsUInt32Number));

    // Call the function under test
    cmsIT8SetPropertyHex(handle, propertyName, value);

    // Clean up
    free(propertyName);
    cmsIT8Free(handle);

    return 0;
}