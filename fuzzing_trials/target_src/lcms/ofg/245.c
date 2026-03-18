#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract meaningful values
    if (size < 4) {
        return 0;
    }

    // Initialize the variables needed for cmsIT8SetPropertyHex
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract a string from the input data
    size_t str_len = size / 2;
    char *property_name = (char *)malloc(str_len + 1);
    if (property_name == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(property_name, data, str_len);
    property_name[str_len] = '\0';

    // Extract a cmsUInt32Number from the input data
    cmsUInt32Number value = *(cmsUInt32Number *)(data + str_len);

    // Call the function-under-test
    cmsBool result = cmsIT8SetPropertyHex(handle, property_name, value);

    // Clean up
    free(property_name);
    cmsIT8Free(handle);

    return 0;
}