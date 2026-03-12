#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle;
    char *columnName;

    // Check if the input size is sufficient to form a valid column name
    if (size == 0) {
        return 0;
    }

    // Create a dummy IT8 handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    columnName = (char *)malloc(size + 1);
    if (columnName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }

    memcpy(columnName, data, size);
    columnName[size] = '\0';

    // Call the function-under-test
    cmsBool result = cmsIT8SetIndexColumn(handle, columnName);

    // Check the result to ensure the function is being executed properly
    if (!result) {
        fprintf(stderr, "cmsIT8SetIndexColumn failed for column name: %s\n", columnName);
    }

    // Clean up
    free(columnName);
    cmsIT8Free(handle);

    return 0;
}