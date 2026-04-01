#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsColorSpaceSignature colorSpace;

    // Ensure that size is sufficient to extract necessary data
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Create a profile using a built-in profile to ensure it's not NULL
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract colorSpace from the input data
    colorSpace = *(cmsColorSpaceSignature*)data;

    // Call the function-under-test
    cmsSetPCS(hProfile, colorSpace);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}