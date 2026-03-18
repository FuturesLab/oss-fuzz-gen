#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2_plugin.h>
#include <lcms2.h>  // Include the main Little CMS library for necessary types and functions
#include "/src/lcms/include/lcms2.h"  // Include the additional header as instructed

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char **formats = NULL;
    int result;

    // Initialize handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Use the input data to populate the handle
    if (size > 0) {
        // Assuming the input data is a string, attempt to use it as IT8 data
        char *inputData = (char *)malloc(size + 1);
        if (inputData != NULL) {
            memcpy(inputData, data, size);
            inputData[size] = '\0';  // Null-terminate the string

            // Load the input data into the handle
            if (!cmsIT8LoadFromMem(handle, inputData, size)) {
                free(inputData);
                cmsIT8Free(handle);
                return 0;
            }

            free(inputData);
        }
    }

    // Call the function-under-test
    result = cmsIT8EnumDataFormat(handle, &formats);

    // Clean up
    if (formats != NULL) {
        // Use the correct function to free the formats
        cmsIT8Free(formats);
    }
    cmsIT8Free(handle);

    return 0;
}