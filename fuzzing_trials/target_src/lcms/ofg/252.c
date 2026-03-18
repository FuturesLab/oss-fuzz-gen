#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number Intent;
    cmsUInt32Number Flags;
    cmsBool result;

    // Ensure size is sufficient to extract parameters
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Initialize the parameters from the input data
    Intent = *(cmsUInt32Number *)data;
    Flags = *(cmsUInt32Number *)(data + sizeof(cmsUInt32Number));

    // Create a dummy profile for fuzzing
    hProfile = cmsCreate_sRGBProfile();

    // Call the function under test
    result = cmsIsCLUT(hProfile, Intent, Flags);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}