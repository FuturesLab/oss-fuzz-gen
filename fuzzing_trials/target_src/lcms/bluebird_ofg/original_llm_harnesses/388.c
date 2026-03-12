#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_388(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE profile;
    cmsColorSpaceSignature colorSpace;

    // Check if the input size is sufficient to extract a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Initialize the profile with a dummy profile
    profile = cmsCreate_sRGBProfile();
    if (profile == NULL) {
        return 0;
    }

    // Extract the cmsColorSpaceSignature from the input data
    colorSpace = *(cmsColorSpaceSignature *)data;

    // Call the function-under-test
    cmsSetColorSpace(profile, colorSpace);

    // Clean up the profile
    cmsCloseProfile(profile);

    return 0;
}