#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsHPROFILE create_dummy_profile() {
    return cmsCreate_sRGBProfile();
}

static cmsHTRANSFORM create_dummy_transform() {
    cmsHPROFILE hProfiles[2];
    hProfiles[0] = create_dummy_profile();
    hProfiles[1] = create_dummy_profile();
    cmsHTRANSFORM transform = cmsCreateMultiprofileTransform(
        hProfiles, 2, TYPE_RGB_8, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    cmsCloseProfile(hProfiles[0]);
    cmsCloseProfile(hProfiles[1]);
    return transform;
}

int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 3) {
        return 0;
    } // Ensure there is enough data for stride operations

    cmsHTRANSFORM transform = create_dummy_transform();
    if (!transform) {
        return 0;
    }

    // cmsDoTransformStride
    size_t outputSize = Size / 3 * 3; // Ensure output buffer is properly sized
    void *outputBuffer = malloc(outputSize);
    if (outputBuffer) {
        cmsDoTransformStride(transform, Data, outputBuffer, Size / 3, 3);
        free(outputBuffer);
    }

    // cmsDoTransformLineStride
    outputBuffer = malloc(outputSize);
    if (outputBuffer) {
        cmsDoTransformLineStride(transform, Data, outputBuffer, 1, Size / 3, 3, 3, 3, 3);
        free(outputBuffer);
    }

    // cmsGetTransformInputFormat

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsGetTransformInputFormat with cmsGetTransformOutputFormat
    cmsUInt32Number inputFormat = cmsGetTransformOutputFormat(transform);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // cmsDoTransform
    outputBuffer = malloc(outputSize);
    if (outputBuffer) {
        cmsDoTransform(transform, Data, outputBuffer, Size / 3);
        free(outputBuffer);
    }

    // cmsCreateProofingTransform
    cmsHPROFILE proofingProfile = create_dummy_profile();
    cmsHTRANSFORM proofingTransform = cmsCreateProofingTransform(
        create_dummy_profile(), inputFormat,
        create_dummy_profile(), inputFormat,
        proofingProfile, INTENT_PERCEPTUAL,
        INTENT_ABSOLUTE_COLORIMETRIC, 0);
    if (proofingTransform) {
        cmsDeleteTransform(proofingTransform);
    }
    cmsCloseProfile(proofingProfile);

    cmsDeleteTransform(transform);
    return 0;
}