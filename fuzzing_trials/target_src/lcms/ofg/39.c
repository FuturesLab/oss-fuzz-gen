#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHANDLE handle;
    const char *propertyName;
    cmsFloat64Number value;

    // Ensure size is large enough to extract a double value and a property name
    if (size < sizeof(cmsFloat64Number) + 1) {
        return 0;
    }

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract a double value from the input data
    memcpy(&value, data, sizeof(cmsFloat64Number));

    // Extract a property name from the input data
    propertyName = (const char *)(data + sizeof(cmsFloat64Number));

    // Ensure the property name is null-terminated
    char *propertyNameCopy = (char *)malloc(size - sizeof(cmsFloat64Number) + 1);
    if (propertyNameCopy == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyNameCopy, propertyName, size - sizeof(cmsFloat64Number));
    propertyNameCopy[size - sizeof(cmsFloat64Number)] = '\0';

    // Call the function-under-test
    cmsBool result = cmsIT8SetPropertyDbl(handle, propertyNameCopy, value);

    // Clean up
    free(propertyNameCopy);
    cmsIT8Free(handle);

    return 0;
}