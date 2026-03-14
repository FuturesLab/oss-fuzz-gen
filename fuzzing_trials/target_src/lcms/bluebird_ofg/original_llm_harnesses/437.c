#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_437(const uint8_t *data, size_t size) {
    cmsHPROFILE profiles[2];
    cmsUInt32Number nProfiles = 2;
    cmsUInt32Number inputFormat = TYPE_RGB_8;
    cmsUInt32Number outputFormat = TYPE_RGB_8;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    // Initialize profiles with dummy profiles
    profiles[0] = cmsCreate_sRGBProfile();
    profiles[1] = cmsCreate_sRGBProfile();

    // Call the function-under-test
    cmsHTRANSFORM transform = cmsCreateMultiprofileTransform(
        profiles, nProfiles, inputFormat, outputFormat, intent, flags);

    // Clean up
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }
    cmsCloseProfile(profiles[0]);
    cmsCloseProfile(profiles[1]);

    return 0;
}