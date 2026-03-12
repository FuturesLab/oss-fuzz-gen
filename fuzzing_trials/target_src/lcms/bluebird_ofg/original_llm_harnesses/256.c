#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h> // Assuming Little CMS library is used

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Initialize the parameters for cmsIT8SetDataRowCol
    cmsHANDLE handle;
    int row, col;
    const char *text;

    // Ensure the size is sufficient to extract at least the row, col, and a text string
    if (size < sizeof(int) * 2 + 1) {
        return 0;
    }

    // Extract row and col from the data
    row = *((int*)data);
    col = *((int*)(data + sizeof(int)));

    // Extract text from the remaining data
    text = (const char*)(data + sizeof(int) * 2);

    // Create a dummy cmsHANDLE for testing
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataRowCol(handle, row, col, text);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}