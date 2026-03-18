#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char propertyName[256];

    // Initialize the handle with a valid cmsHANDLE object
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the propertyName is null-terminated and non-empty
    if (size > 0) {
        size_t copySize = size < sizeof(propertyName) - 1 ? size : sizeof(propertyName) - 1;
        memcpy(propertyName, data, copySize);
        propertyName[copySize] = '\0';
    } else {
        strcpy(propertyName, "DefaultPropertyName");
    }

    // Call the function-under-test
    cmsFloat64Number result = cmsIT8GetPropertyDbl(handle, propertyName);

    // Free the allocated handle
    cmsIT8Free(handle);

    return 0;
}