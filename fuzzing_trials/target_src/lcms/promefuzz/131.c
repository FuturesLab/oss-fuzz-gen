// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateTransform at cmsxform.c:1355:32 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsDoTransformStride at cmsxform.c:211:16 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsGetTransformInputFormat at cmsxform.c:1429:27 in lcms2.h
// cmsGetTransformOutputFormat at cmsxform.c:1437:27 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1398:25 in lcms2.h
// cmsCreateMultiprofileTransform at cmsxform.c:1316:25 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsHPROFILE create_dummy_profile() {
    return (cmsHPROFILE)malloc(1);  // Dummy profile representation
}

static void destroy_dummy_profile(cmsHPROFILE profile) {
    free(profile);
}

static cmsHTRANSFORM create_dummy_transform() {
    return cmsCreateTransform(NULL, TYPE_RGB_8, NULL, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
}

static void destroy_dummy_transform(cmsHTRANSFORM transform) {
    cmsDeleteTransform(transform);
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Dummy profiles
    cmsHPROFILE inputProfile = create_dummy_profile();
    cmsHPROFILE outputProfile = create_dummy_profile();
    cmsHPROFILE proofingProfile = create_dummy_profile();
    cmsHPROFILE profiles[2] = { inputProfile, outputProfile };

    // Create a dummy transform
    cmsHTRANSFORM transform = create_dummy_transform();
    if (transform == NULL) {
        destroy_dummy_profile(inputProfile);
        destroy_dummy_profile(outputProfile);
        destroy_dummy_profile(proofingProfile);
        return 0;
    }

    // Buffers for transformation
    void *inputBuffer = malloc(Size);
    void *outputBuffer = malloc(Size);
    if (!inputBuffer || !outputBuffer) {
        free(inputBuffer);
        free(outputBuffer);
        destroy_dummy_profile(inputProfile);
        destroy_dummy_profile(outputProfile);
        destroy_dummy_profile(proofingProfile);
        destroy_dummy_transform(transform);
        return 0;
    }
    memcpy(inputBuffer, Data, Size);

    // Invoke cmsDoTransformStride
    cmsDoTransformStride(transform, inputBuffer, outputBuffer, Size, Size);

    // Invoke cmsDoTransform
    cmsDoTransform(transform, inputBuffer, outputBuffer, Size);

    // Get input/output format
    cmsUInt32Number inputFormat = cmsGetTransformInputFormat(transform);
    cmsUInt32Number outputFormat = cmsGetTransformOutputFormat(transform);

    // Create proofing transform
    cmsHTRANSFORM proofingTransform = cmsCreateProofingTransform(
        inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, 0, 0, 0);

    // Create multiprofile transform
    cmsHTRANSFORM multiProfileTransform = cmsCreateMultiprofileTransform(
        profiles, 2, inputFormat, outputFormat, 0, 0);

    // Cleanup
    free(inputBuffer);
    free(outputBuffer);
    destroy_dummy_profile(inputProfile);
    destroy_dummy_profile(outputProfile);
    destroy_dummy_profile(proofingProfile);
    destroy_dummy_transform(transform);
    destroy_dummy_transform(proofingTransform);
    destroy_dummy_transform(multiProfileTransform);

    return 0;
}