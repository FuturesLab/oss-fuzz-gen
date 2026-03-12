#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    // Initialize the cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Ensure the input data is null-terminated
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        cmsIT8Free(handle);
        return 0; // Memory allocation failed, exit early
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Ensure the input data is in a format that can be processed
    // For example, we can simulate a simple IT8 format header
    // This is a minimal example and can be adjusted based on the actual expected format
    if (size > 0 && strncmp(inputData, "IT8", 3) == 0) {
        // Call the function-under-test
        cmsIT8FindDataFormat(handle, inputData);
    }

    // Clean up
    free(inputData);
    cmsIT8Free(handle);

    return 0;
}