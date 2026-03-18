#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_466(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsHPROFILE inputProfile, outputProfile;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Create dummy profiles for input and output
    inputProfile = cmsCreate_sRGBProfile();
    outputProfile = cmsCreate_sRGBProfile();

    if (inputProfile == NULL || outputProfile == NULL) {
        if (inputProfile != NULL) cmsCloseProfile(inputProfile);
        if (outputProfile != NULL) cmsCloseProfile(outputProfile);
        return 0;
    }

    // Create a transform
    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, intent, flags);

    // Clean up profiles
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    if (transform != NULL) {
        // Call the function-under-test
        cmsDeleteTransform(transform);
    }

    return 0;
}