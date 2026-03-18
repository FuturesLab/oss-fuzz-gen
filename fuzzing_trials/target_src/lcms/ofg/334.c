#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_334(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    const void *mem = (const void *)data;
    cmsUInt32Number memSize = (cmsUInt32Number)size;

    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromMemTHR(context, mem, memSize);

    // If a profile was successfully created, close it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}