#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_464(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHPROFILE hProfile;
    cmsTagSignature sig1, sig2;

    // Check if the size is sufficient to extract two cmsTagSignature values
    if (size < 2 * sizeof(cmsTagSignature)) {
        return 0;
    }

    // Create a profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract cmsTagSignature values from the input data
    sig1 = *(cmsTagSignature*)data;
    sig2 = *(cmsTagSignature*)(data + sizeof(cmsTagSignature));

    // Call the function-under-test
    cmsBool result = cmsLinkTag(hProfile, sig1, sig2);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}