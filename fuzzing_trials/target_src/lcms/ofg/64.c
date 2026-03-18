#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsUInt32Number model;

    // Check if size is sufficient to extract a cmsUInt32Number
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

    // Close the profile after testing
    cmsCloseProfile(hProfile);

    return 0;
}