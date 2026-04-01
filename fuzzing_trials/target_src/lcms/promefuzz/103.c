// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateMultiprofileTransform at cmsxform.c:1316:25 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDoTransformStride at cmsxform.c:211:16 in lcms2.h
// cmsDoTransformLineStride at cmsxform.c:229:16 in lcms2.h
// cmsGetTransformInputFormat at cmsxform.c:1429:27 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1398:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

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

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0; // Ensure there is enough data for stride operations

    cmsHTRANSFORM transform = create_dummy_transform();
    if (!transform) return 0;

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
    cmsUInt32Number inputFormat = cmsGetTransformInputFormat(transform);

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