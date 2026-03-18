#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsFloat64Number version;
    cmsUInt32Number flags;
    cmsHPROFILE profile;

    // Initialize the parameters with non-NULL values
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    if (inputProfile == NULL || outputProfile == NULL) {
        if (inputProfile != NULL) cmsCloseProfile(inputProfile);
        if (outputProfile != NULL) cmsCloseProfile(outputProfile);
        return 0;
    }

    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    version = 4.3; // Example version number
    flags = 0; // Example flags, can be varied

    // Ensure transform is valid before proceeding
    if (transform == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test
    profile = cmsTransform2DeviceLink(transform, version, flags);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}