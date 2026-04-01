#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsBool result;

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    result = cmsMD5computeID(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}