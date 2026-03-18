#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHPROFILE hProfile;
    cmsProfileClassSignature profileClassSignature;

    // Check if size is sufficient to extract a cmsProfileClassSignature
    if (size < sizeof(cmsProfileClassSignature)) {
        return 0;
    }

    // Create a dummy profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract cmsProfileClassSignature from data
    profileClassSignature = *(cmsProfileClassSignature *)data;

    // Call the function-under-test
    cmsSetDeviceClass(hProfile, profileClassSignature);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}