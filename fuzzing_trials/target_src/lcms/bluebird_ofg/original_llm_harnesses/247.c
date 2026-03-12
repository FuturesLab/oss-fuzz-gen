#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHPROFILE hProfile = NULL;
    cmsFloat64Number result = 0.0;
    cmsFloat64Number gammaValue = 1.0; // Default gamma value

    // Check if the input data size is sufficient to create a profile
    if (size >= sizeof(cmsHPROFILE)) {
        // Create a profile from the input data
        hProfile = cmsOpenProfileFromMem(data, size);
    }

    // If the profile creation was successful, proceed
    if (hProfile != NULL) {
        // Call the function-under-test
        result = cmsDetectRGBProfileGamma(hProfile, gammaValue);

        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    return 0;
}