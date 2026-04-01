#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_355(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle;
    int row, col;
    cmsFloat64Number result;

    // Ensure the size is sufficient to extract row and col
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract row and col from data
    row = *((int*)data);
    col = *((int*)(data + sizeof(int)));

    // Call the function-under-test
    result = cmsIT8GetDataRowColDbl(handle, row, col);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}