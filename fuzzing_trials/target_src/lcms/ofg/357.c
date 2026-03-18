#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_357(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    cmsHANDLE handle;
    const char *propertyName;
    const char **propertyValues;

    // Ensure the data is large enough to extract meaningful inputs
    if (size < 2) {
        return 0;
    }

    // Initialize the handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Use part of the data as the property name
    size_t propertyNameLength = size / 2;
    char *propertyNameBuffer = (char *)malloc(propertyNameLength + 1);
    if (propertyNameBuffer == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyNameBuffer, data, propertyNameLength);
    propertyNameBuffer[propertyNameLength] = '\0';
    propertyName = propertyNameBuffer;

    // Call the function-under-test
    cmsUInt32Number result = cmsIT8EnumPropertyMulti(handle, propertyName, &propertyValues);

    // Clean up
    free(propertyNameBuffer);
    cmsIT8Free(handle);

    return 0;
}