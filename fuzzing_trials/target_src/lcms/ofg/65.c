#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsColorSpaceSignature colorSpace;

    // Ensure the size is sufficient to extract values
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Initialize the profile using a built-in profile for demonstration
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract the cmsColorSpaceSignature from the input data
    colorSpace = *(cmsColorSpaceSignature*)data;

    // Call the function-under-test
    cmsSetPCS(hProfile, colorSpace);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}