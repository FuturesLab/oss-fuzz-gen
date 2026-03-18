#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    cmsCIEXYZ blackPoint;
    cmsHPROFILE hProfile;
    cmsUInt32Number intent = 0; // Rendering intent
    cmsUInt32Number flags = 0; // Flags for cmsDetectBlackPoint

    // Initialize blackPoint with some values
    blackPoint.X = 0.0;
    blackPoint.Y = 0.0;
    blackPoint.Z = 0.0;

    // Create a dummy profile for testing
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsDetectBlackPoint(&blackPoint, hProfile, intent, flags);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}