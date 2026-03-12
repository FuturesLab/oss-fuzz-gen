#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number model;

    // Check if the size is sufficient to extract a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract cmsUInt32Number from the input data
    model = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSetHeaderModel(hProfile, model);

    // Close the profile to avoid memory leaks
    cmsCloseProfile(hProfile);

    return 0;
}