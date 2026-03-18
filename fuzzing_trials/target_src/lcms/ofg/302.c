#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    // Initialize the CMS context
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Check if size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Create a memory-based profile using the input data
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Do something with the profile if needed
        // For example, we can release it immediately
        cmsCloseProfile(profile);
    }

    // Free the CMS context
    cmsDeleteContext(context);

    return 0;
}