#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/lcms/include/lcms2_plugin.h"

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *patchName;

    // Initialize the handle with some valid data
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure that the data can be used as a null-terminated string
    patchName = (char *)malloc(size + 1);
    if (patchName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(patchName, data, size);
    patchName[size] = '\0';

    // Call the function under test
    cmsIT8GetPatchByName(handle, patchName);

    // Clean up
    free(patchName);
    cmsIT8Free(handle);

    return 0;
}