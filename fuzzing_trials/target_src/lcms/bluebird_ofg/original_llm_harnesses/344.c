#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <lcms2.h>

// Fuzzing harness for cmsIT8GetDataRowCol
int LLVMFuzzerTestOneInput_344(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    int row, col;
    const char *result;

    // Initialize handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure size is sufficient to extract two integers for row and col
    if (size < sizeof(int) * 2) {
        cmsIT8Free(handle);
        return 0;
    }

    // Extract row and col from the input data
    row = *((int*)data);
    col = *((int*)(data + sizeof(int)));

    // Call the function-under-test
    result = cmsIT8GetDataRowCol(handle, row, col);

    // Print the result for debugging purposes
    if (result != NULL) {
        printf("Result: %s\n", result);
    }

    // Free the allocated handle
    cmsIT8Free(handle);

    return 0;
}