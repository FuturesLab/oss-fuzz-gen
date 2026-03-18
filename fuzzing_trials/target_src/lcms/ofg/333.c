#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsHPROFILE profile;

    // Initialize a context
    context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Ensure size is non-zero for cmsOpenProfileFromMemTHR
    if (size > 0) {
        // Call the function-under-test
        profile = cmsOpenProfileFromMemTHR(context, (const void *)data, (cmsUInt32Number)size);

        // If a profile is successfully opened, close it
        if (profile != NULL) {
            cmsCloseProfile(profile);
        }
    }

    // Free the context
    cmsDeleteContext(context);

    return 0;
}