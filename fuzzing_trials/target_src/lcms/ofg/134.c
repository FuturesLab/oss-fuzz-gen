#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data
    cmsHPROFILE profile = cmsOpenProfileFromMemTHR(context, data, size);

    // Check if profile creation was successful
    if (profile != NULL) {
        // Call the function-under-test
        cmsProfileClassSignature deviceClass = cmsGetDeviceClass(profile);

        // You can add additional checks or processing here if needed

        // Close the profile
        cmsCloseProfile(profile);
    }

    // Free the memory context
    cmsDeleteContext(context);

    return 0;
}