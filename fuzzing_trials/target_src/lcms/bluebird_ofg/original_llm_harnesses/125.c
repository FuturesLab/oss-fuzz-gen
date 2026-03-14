#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsProfileClassSignature profileClassSignature;

    // Create a dummy profile for fuzzing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0; // Exit if profile creation fails
    }

    // Ensure the size is sufficient to extract a cmsProfileClassSignature
    if (size < sizeof(cmsProfileClassSignature)) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Extract cmsProfileClassSignature from the input data
    profileClassSignature = *(cmsProfileClassSignature *)data;

    // Call the function-under-test
    cmsSetDeviceClass(hProfile, profileClassSignature);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}