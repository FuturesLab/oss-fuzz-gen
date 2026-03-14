#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    const char *propertyName;
    const char **propertyValues;
    cmsUInt32Number result;

    // Initialize the handle to a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure data is not empty and use it for propertyName
    if (size > 0) {
        propertyName = (const char *)data;
    } else {
        propertyName = "defaultPropertyName";
    }

    // Initialize propertyValues to a non-NULL value
    propertyValues = (const char **)malloc(sizeof(char *) * 2);
    if (propertyValues == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    propertyValues[0] = "Value1";
    propertyValues[1] = NULL;

    // Call the function under test
    result = cmsIT8EnumPropertyMulti(handle, propertyName, &propertyValues);

    // Clean up
    free(propertyValues);
    cmsIT8Free(handle);

    return 0;
}