#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Initialize cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Check if the input data is large enough to be used meaningfully
    if (size < 1) {
        cmsIT8Free(handle);
        return 0;
    }

    // Allocate memory for char**
    char **formatList = (char **)malloc(sizeof(char *) * 10); // Assuming a maximum of 10 formats
    if (formatList == NULL) {
        cmsIT8Free(handle);
        return 0;
    }

    // Initialize the formatList with non-NULL values
    for (int i = 0; i < 10; i++) {
        formatList[i] = (char *)malloc(20); // Allocate 20 bytes for each format string
        if (formatList[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(formatList[j]);
            }
            free(formatList);
            cmsIT8Free(handle);
            return 0;
        }
        // Fill the format string with data from input, ensuring null termination
        snprintf(formatList[i], 20, "Format %d", i);
    }

    // Allocate a buffer for the property string and ensure it's null-terminated
    char *propertyStr = (char *)malloc(size + 1);
    if (propertyStr == NULL) {
        for (int i = 0; i < 10; i++) {
            free(formatList[i]);
        }
        free(formatList);
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyStr, data, size);
    propertyStr[size] = '\0'; // Null-terminate the string

    // Use the input data to simulate a real-world scenario
    // For demonstration, let's assume the input data is used to set a property in the handle
    cmsIT8SetPropertyStr(handle, "SampleProperty", propertyStr);

    // Call the function-under-test
    int result = cmsIT8EnumDataFormat(handle, formatList);

    // Clean up
    free(propertyStr);
    for (int i = 0; i < 10; i++) {
        free(formatList[i]);
    }
    free(formatList);
    cmsIT8Free(handle);

    return 0;
}