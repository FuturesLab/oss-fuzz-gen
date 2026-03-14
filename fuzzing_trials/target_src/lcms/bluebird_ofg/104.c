#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    if (size < 8) {
        return 0;
    }

    cmsUInt32Number inputFormat = *(cmsUInt32Number*)(data);
    cmsUInt32Number outputFormat = *(cmsUInt32Number*)(data + 4);

    cmsHPROFILE hInputProfile = cmsCreate_sRGBProfile();
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreate_sRGBProfile to cmsGetTagCount

    cmsInt32Number ret_cmsGetTagCount_bzxyk = cmsGetTagCount(hInputProfile);
    if (ret_cmsGetTagCount_bzxyk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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