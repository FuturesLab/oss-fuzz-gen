#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2_plugin.h>

// Define the fuzzing function
int LLVMFuzzerTestOneInput_345(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle;
    int row = 0;
    int col = 0;

    // Check if the input size is sufficient to extract parameters
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Extract row and col from the input data
    row = *((int*)data);
    col = *((int*)(data + sizeof(int)));

    // Initialize the handle with a valid cmsHANDLE value
    handle = cmsIT8Alloc(cmsCreateContext(NULL, NULL));
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *result = cmsIT8GetDataRowCol(handle, row, col);

    // Print the result for debugging purposes
    if (result != NULL) {
        printf("Result: %s\n", result);
    }

    // Clean up
    cmsIT8Free(handle);

    return 0;
}