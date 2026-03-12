#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <lcms2_plugin.h>

int LLVMFuzzerTestOneInput_354(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    int row, col;
    cmsFloat64Number result;

    // Initialize handle to a valid non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure there is enough data to extract row and col
    if (size < sizeof(int) * 2) {
        cmsIT8Free(handle);
        return 0;
    }

    // Extract row and col from data
    row = *(int *)(data);
    col = *(int *)(data + sizeof(int));

    // Call the function-under-test
    result = cmsIT8GetDataRowColDbl(handle, row, col);

    // Output the result for debugging purposes
    printf("Result: %f\n", result);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}