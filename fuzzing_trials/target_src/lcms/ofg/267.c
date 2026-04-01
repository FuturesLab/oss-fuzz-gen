#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt32Number)) {
        return 0; // Ensure there's enough data for cmsUInt32Number
    }

    // Initialize a cmsHPROFILE object
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0; // If profile creation fails, exit
    }

    // Extract cmsUInt32Number from the input data
    cmsUInt32Number version = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSetEncodedICCversion(hProfile, version);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}