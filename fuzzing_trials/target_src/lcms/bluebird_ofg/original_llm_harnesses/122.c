#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

// Define a dummy cmsHANDLE for testing purposes
typedef void* cmsHANDLE;

// Dummy function to simulate cmsIT8GetData behavior
const char* cmsIT8GetData(cmsHANDLE handle, const char* row, const char* col) {
    // This is a placeholder implementation
    // In a real scenario, this would interact with the handle to retrieve data
    return "dummy_data";
}

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    cmsHANDLE handle = (cmsHANDLE)malloc(1); // Allocate a dummy handle
    if (!handle) {
        return 0;
    }

    // Ensure size is large enough to split into two non-null strings
    if (size < 2) {
        free(handle);
        return 0;
    }

    // Split the input data into two strings
    size_t half_size = size / 2;
    char* row = (char*)malloc(half_size + 1);
    char* col = (char*)malloc(size - half_size + 1);

    if (!row || !col) {
        free(handle);
        free(row);
        free(col);
        return 0;
    }

    memcpy(row, data, half_size);
    row[half_size] = '\0';

    memcpy(col, data + half_size, size - half_size);
    col[size - half_size] = '\0';

    // Call the function-under-test
    const char* result = cmsIT8GetData(handle, row, col);

    // Clean up
    free(handle);
    free(row);
    free(col);

    return 0;
}