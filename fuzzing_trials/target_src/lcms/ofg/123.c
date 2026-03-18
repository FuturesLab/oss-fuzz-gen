#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *firstString, *secondString;
    const char *result;

    // Ensure the data is large enough to be split into two non-null strings
    if (size < 2) return 0;

    // Initialize the handle
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) return 0;

    // Allocate memory for the strings and ensure they are null-terminated
    firstString = (char *)malloc(size / 2 + 1);
    secondString = (char *)malloc(size / 2 + 1);

    if (firstString == NULL || secondString == NULL) {
        cmsIT8Free(handle);
        free(firstString);
        free(secondString);
        return 0;
    }

    // Copy data into the strings
    memcpy(firstString, data, size / 2);
    firstString[size / 2] = '\0';
    memcpy(secondString, data + size / 2, size / 2);
    secondString[size / 2] = '\0';

    // Call the function-under-test
    result = cmsIT8GetData(handle, firstString, secondString);

    // Clean up
    cmsIT8Free(handle);
    free(firstString);
    free(secondString);

    return 0;
}