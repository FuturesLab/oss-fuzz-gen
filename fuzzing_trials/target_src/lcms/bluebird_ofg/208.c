#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    if (size < 8) {
        return 0;
    }

    cmsUInt32Number inputFormat = *(cmsUInt32Number*)(data);
    cmsUInt32Number outputFormat = *(cmsUInt32Number*)(data + 4);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCreate_sRGBProfile with cmsCreateXYZProfile
    cmsHPROFILE hInputProfile = cmsCreateXYZProfile();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    cmsHPROFILE hOutputProfile = cmsCreate_sRGBProfile();

    if (hInputProfile == NULL || hOutputProfile == NULL) {
        if (hInputProfile != NULL) {
                cmsCloseProfile(hInputProfile);
        }
        if (hOutputProfile != NULL) {
                cmsCloseProfile(hOutputProfile);
        }
        return 0;
    }

    cmsHTRANSFORM transform = cmsCreateTransform(hInputProfile, inputFormat, hOutputProfile, outputFormat, INTENT_PERCEPTUAL, 0);

    if (transform == NULL) {
        cmsCloseProfile(hInputProfile);
        cmsCloseProfile(hOutputProfile);
        return 0;
    }

    // Create a small buffer to transform
    uint8_t inputBuffer[4] = {0, 0, 0, 0};
    uint8_t outputBuffer[4] = {0};

    // Perform the transformation
    cmsDoTransform(transform, inputBuffer, outputBuffer, 1);

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(hInputProfile);
    cmsCloseProfile(hOutputProfile);

    return 0;
}