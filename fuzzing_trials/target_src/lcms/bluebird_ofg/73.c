#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsFloat64Number version;
    cmsUInt32Number flags;
    cmsHPROFILE profile;

    // Initialize the parameters with non-NULL values
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    if (inputProfile == NULL || outputProfile == NULL) {
        if (inputProfile != NULL) {
                cmsCloseProfile(inputProfile);
        }
        if (outputProfile != NULL) {
                cmsCloseProfile(outputProfile);
        }
        return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsCreateTransform
    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, inputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    version = 4.3; // Example version number
    flags = 0; // Example flags, can be varied

    // Ensure transform is valid before proceeding
    if (transform == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsTransform2DeviceLink
    profile = cmsTransform2DeviceLink(transform, version, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}