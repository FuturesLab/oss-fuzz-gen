#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_339(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data
    cmsHPROFILE profile = cmsOpenProfileFromMemTHR(context, data, size);

    // Check if the profile is valid
    if (profile != NULL) {
        // Call the function-under-test
        cmsUInt32Number version = cmsGetEncodedICCversion(profile);

        // Use the version in some way to prevent it from being optimized away
        if (version == 0) {
            // Do something trivial
            version = 1;
        }

        // Close the profile
        cmsCloseProfile(profile);
    }

    // Free the memory context
    cmsDeleteContext(context);

    return 0;
}