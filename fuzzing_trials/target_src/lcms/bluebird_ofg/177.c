#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *sheetType;

    // Initialize handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure that the input size is sufficient to perform meaningful operations
    if (size == 0) {
        cmsIT8Free(handle);
        return 0;
    }

    // Allocate and copy data to sheetType, ensuring null-termination
    sheetType = (char *)malloc(size + 1);
    if (sheetType == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(sheetType, data, size);
    sheetType[size] = '\0';

    // Attempt to set the sheet type
    if (cmsIT8SetSheetType(handle, sheetType) == FALSE) {
        // If setting the sheet type fails, clean up and return
        free(sheetType);
        cmsIT8Free(handle);
        return 0;
    }

    // Additional operations to increase code coverage
    // Attempt to retrieve the sheet type to ensure the function was successful
    const char *retrievedSheetType = cmsIT8GetSheetType(handle);
    if (retrievedSheetType != NULL) {
        // Perform some operations with the retrieved sheet type
        // For example, compare it with the original or check its length
        if (strcmp(retrievedSheetType, sheetType) == 0) {
            // Additional operations if needed
        }
    }

    // Clean up
    free(sheetType);
    cmsIT8Free(handle);

    return 0;
}