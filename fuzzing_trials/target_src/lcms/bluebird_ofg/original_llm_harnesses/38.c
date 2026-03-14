#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *propertyName;
    cmsFloat64Number propertyValue;

    if (size < sizeof(cmsFloat64Number) + 1) {
        return 0;
    }

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract propertyValue from the input data
    memcpy(&propertyValue, data, sizeof(cmsFloat64Number));

    // Create a null-terminated string for propertyName
    propertyName = (char *)malloc(size - sizeof(cmsFloat64Number) + 1);
    if (propertyName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyName, data + sizeof(cmsFloat64Number), size - sizeof(cmsFloat64Number));
    propertyName[size - sizeof(cmsFloat64Number)] = '\0';

    // Call the function-under-test
    cmsIT8SetPropertyDbl(handle, propertyName, propertyValue);

    // Clean up
    free(propertyName);
    cmsIT8Free(handle);

    return 0;
}