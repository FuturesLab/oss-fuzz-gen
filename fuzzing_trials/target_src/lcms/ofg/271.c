#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    // Initialize the context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data if size is sufficient
    cmsHPROFILE profile = NULL;
    if (size > 0) {
        profile = cmsOpenProfileFromMemTHR(context, data, size);
    }

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}