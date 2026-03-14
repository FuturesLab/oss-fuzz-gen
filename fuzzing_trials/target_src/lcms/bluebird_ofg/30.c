#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"
#include <string.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsHANDLE handle;
    int row, col;
    cmsFloat64Number value;

    // Ensure the data size is sufficient for extracting the parameters
    if (size < sizeof(cmsHANDLE) + 2 * sizeof(int) + sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Create a new IT8 handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // Allocation failed, return
    }

    // Extract values from the input data
    // Note: We should not directly cast data to cmsHANDLE, instead we use a valid cmsIT8 handle
    row = (int)*(int*)data;
    data += sizeof(int);
    size -= sizeof(int);

    col = (int)*(int*)data;
    data += sizeof(int);
    size -= sizeof(int);

    value = (cmsFloat64Number)*(double*)data;

    // Ensure row and col are within a reasonable range to prevent out-of-bounds access
    row = row % 100; // Assuming a maximum of 100 rows
    col = col % 100; // Assuming a maximum of 100 columns

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataRowColDbl(handle, row, col, value);

    // Free the IT8 handle
    cmsIT8Free(handle);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}