#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsHTRANSFORM transform;
    cmsUInt32Number inputFormat;
    cmsUInt32Number outputFormat;

    // Check if the size is sufficient to extract required data
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Initialize the parameters with data
    // Since we cannot directly use uninitialized or arbitrary memory for cmsHTRANSFORM,
    // we will create a dummy transform for testing purposes.
    cmsHPROFILE srcProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE dstProfile = cmsCreate_sRGBProfile();

    if (srcProfile == NULL || dstProfile == NULL) {
        if (srcProfile) {
                cmsCloseProfile(srcProfile);
        }
        if (dstProfile) {
                cmsCloseProfile(dstProfile);
        }
        return 0;
    }

    inputFormat = *(cmsUInt32Number*)data;
    outputFormat = *(cmsUInt32Number*)(data + sizeof(cmsUInt32Number));


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of cmsCreateTransform
    transform = cmsCreateTransform(srcProfile, inputFormat, dstProfile, outputFormat, INTENT_PERCEPTUAL, D_CALCULATE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (transform == NULL) {
        cmsCloseProfile(srcProfile);
        cmsCloseProfile(dstProfile);
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsChangeBuffersFormat(transform, inputFormat, outputFormat);

    // Use the result to avoid compiler optimizations
    if (result) {
        // Do something if needed
    }

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(srcProfile);
    cmsCloseProfile(dstProfile);

    return 0;
}