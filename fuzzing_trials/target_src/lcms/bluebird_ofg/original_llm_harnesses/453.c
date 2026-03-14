#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Fuzzing harness for cmsIsMatrixShaper
int LLVMFuzzerTestOneInput_453(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;

    // Ensure we have enough data to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem((void*)data, size);

    // If the profile creation failed, return early
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function under test
    cmsBool result = cmsIsMatrixShaper(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}