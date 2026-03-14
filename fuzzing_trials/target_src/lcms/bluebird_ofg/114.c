#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Initialize the cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the input data is null-terminated for a valid C-string
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0';

    // Call the function under test
    cmsBool result = cmsIT8SetComment(handle, comment);

    // Clean up
    free(comment);
    cmsIT8Free(handle);

    return 0;
}