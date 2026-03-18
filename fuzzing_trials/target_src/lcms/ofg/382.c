#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_382(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    char filename[] = "test.icc";

    // Initialize the profile with some data
    if (size > 0) {
        hProfile = cmsOpenProfileFromMem(data, size);
    } else {
        // If size is 0, create a default profile
        hProfile = cmsCreate_sRGBProfile();
    }

    if (hProfile == NULL) {
        return 0; // Exit if profile creation failed
    }

    // Call the function under test
    cmsBool result = cmsSaveProfileToFile(hProfile, filename);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}