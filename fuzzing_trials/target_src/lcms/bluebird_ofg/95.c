#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure size is sufficient for an integer and a string
    if (size < sizeof(int) + 1) {
        cmsIT8Free(handle);
        return 0;
    }

    // Extract an integer from the data
    int index;
    memcpy(&index, data, sizeof(int));

    // Use the remaining data as a string
    char *patchName = (char *)malloc(size - sizeof(int) + 1);
    if (patchName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(patchName, data + sizeof(int), size - sizeof(int));
    patchName[size - sizeof(int)] = '\0'; // Ensure null-termination

    // Call the function-under-test
    const char *result = cmsIT8GetPatchName(handle, index, patchName);

    // Clean up
    free(patchName);
    cmsIT8Free(handle);

    return 0;
}