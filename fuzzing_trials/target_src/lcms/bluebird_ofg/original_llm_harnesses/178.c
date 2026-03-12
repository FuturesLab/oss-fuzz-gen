#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle = cmsIT8Alloc(NULL); // Allocate a new IT8 handle
    int row = 1; // Example row index
    int col = 1; // Example column index
    cmsFloat64Number value = 1.0; // Example double value

    // Ensure data size is sufficient for fuzzing
    if (size < sizeof(cmsFloat64Number)) {
        cmsIT8Free(handle);
        return 0;
    }

    // Use data to modify the value
    value = *(const cmsFloat64Number*)data;

    // Call the function under test
    cmsBool result = cmsIT8SetDataRowColDbl(handle, row, col, value);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}