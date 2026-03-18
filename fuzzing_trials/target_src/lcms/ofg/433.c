#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_433(const uint8_t *data, size_t size) {
    // Initialize cmsHANDLE and char array
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *sheetType = (char *)malloc(size + 1);
    if (sheetType == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(sheetType, data, size);
    sheetType[size] = '\0';

    // Call the function-under-test
    cmsBool result = cmsIT8SetSheetType(handle, sheetType);

    // Clean up
    free(sheetType);
    cmsIT8Free(handle);

    return 0;
}