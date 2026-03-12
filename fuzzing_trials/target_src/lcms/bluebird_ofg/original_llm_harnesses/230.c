#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free
#include <lcms2_plugin.h>

int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Initialize a cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(0);
    if (handle == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *dataFormat = (char *)malloc(size + 1);
    if (dataFormat == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(dataFormat, data, size);
    dataFormat[size] = '\0';

    // Call the function under test
    int result = cmsIT8FindDataFormat(handle, dataFormat);

    // Clean up
    free(dataFormat);
    cmsIT8Free(handle);

    return 0;
}