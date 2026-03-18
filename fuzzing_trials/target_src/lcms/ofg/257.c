#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    int row, col;
    const char *text;

    // Ensure size is sufficient to extract required data
    if (size < sizeof(int) * 2 + 1) {
        return 0;
    }

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract row and col from data
    row = *((int *)data);
    col = *((int *)(data + sizeof(int)));

    // Ensure text is null-terminated
    text = (const char *)(data + sizeof(int) * 2);
    size_t text_len = size - sizeof(int) * 2;
    char *text_copy = (char *)malloc(text_len + 1);
    if (text_copy == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(text_copy, text, text_len);
    text_copy[text_len] = '\0';

    // Call the function under test
    cmsIT8SetDataRowCol(handle, row, col, text_copy);

    // Clean up
    free(text_copy);
    cmsIT8Free(handle);

    return 0;
}