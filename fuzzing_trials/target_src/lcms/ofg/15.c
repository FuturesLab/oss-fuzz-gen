#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsUInt32Number intent;
    cmsUInt32Number flags;

    // Ensure size is sufficient to extract required parameters
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Extract parameters from input data
    intent = *(const cmsUInt32Number *)data;
    flags = *(const cmsUInt32Number *)(data + sizeof(cmsUInt32Number));

    // Create a dummy profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function under test
    cmsBool result = cmsIsIntentSupported(hProfile, intent, flags);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}