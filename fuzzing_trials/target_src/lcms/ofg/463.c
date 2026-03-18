#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_463(const uint8_t *data, size_t size) {
    // Initialize a memory context for Little CMS
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMemTHR(context, data, size);

    // Check if the profile was created successfully
    if (hProfile != NULL) {
        // Call the function-under-test
        cmsBool result = cmsCloseProfile(hProfile);

        // Optionally, use the result for any further checks or logging
        (void)result; // Suppress unused variable warning
    }

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}