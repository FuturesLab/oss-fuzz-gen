#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static void fuzz_cmsGetSupportedIntents() {
    cmsUInt32Number intentCount = cmsGetSupportedIntents(0, NULL, NULL);

    cmsUInt32Number* Codes = (cmsUInt32Number*)malloc(sizeof(cmsUInt32Number) * intentCount);
    char** Descriptions = (char**)malloc(sizeof(char*) * intentCount);

    if (Codes && Descriptions) {
        cmsGetSupportedIntents(intentCount, Codes, Descriptions);
    }

    free(Codes);
    free(Descriptions);
}

static void fuzz_cmsCreateTransform() {
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();

    if (inputProfile && outputProfile) {
        cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
        if (transform) {
            cmsDeleteTransform(transform);
        }
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
}

static void fuzz_cmsCreateProofingTransformTHR() {
    cmsContext context = NULL;
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    if (inputProfile && outputProfile && proofingProfile) {
        cmsHTRANSFORM transform = cmsCreateProofingTransformTHR(context, inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, proofingProfile, INTENT_PERCEPTUAL, INTENT_PERCEPTUAL, 0);
        if (transform) {
            cmsDeleteTransform(transform);
        }
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);
}

static void fuzz_cmsCreateExtendedTransform() {
    cmsContext context = NULL;
    cmsHPROFILE profiles[2];
    profiles[0] = cmsCreate_sRGBProfile();
    profiles[1] = cmsCreate_sRGBProfile();
    cmsUInt32Number intents[2] = { INTENT_PERCEPTUAL, INTENT_PERCEPTUAL };
    cmsBool bpc[2] = { FALSE, FALSE };
    cmsFloat64Number adaptationStates[2] = { 1.0, 1.0 };

    if (profiles[0] && profiles[1]) {
        cmsHTRANSFORM transform = cmsCreateExtendedTransform(context, 2, profiles, bpc, intents, adaptationStates, NULL, 0, TYPE_RGB_8, TYPE_RGB_8, 0);
        if (transform) {
            cmsDeleteTransform(transform);
        }
    }

    cmsCloseProfile(profiles[0]);
    cmsCloseProfile(profiles[1]);
}

static void fuzz_cmsGetSupportedIntentsTHR() {
    cmsContext context = NULL;
    cmsUInt32Number intentCount = cmsGetSupportedIntentsTHR(context, 0, NULL, NULL);

    cmsUInt32Number* Codes = (cmsUInt32Number*)malloc(sizeof(cmsUInt32Number) * intentCount);
    char** Descriptions = (char**)malloc(sizeof(char*) * intentCount);

    if (Codes && Descriptions) {
        cmsGetSupportedIntentsTHR(context, intentCount, Codes, Descriptions);
    }

    free(Codes);
    free(Descriptions);
}

static void fuzz_cmsCreateMultiprofileTransformTHR() {
    cmsContext context = NULL;
    cmsHPROFILE profiles[2];
    profiles[0] = cmsCreate_sRGBProfile();
    profiles[1] = cmsCreate_sRGBProfile();

    if (profiles[0] && profiles[1]) {
        cmsHTRANSFORM transform = cmsCreateMultiprofileTransformTHR(context, profiles, 2, TYPE_RGB_8, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
        if (transform) {
            cmsDeleteTransform(transform);
        }
    }

    cmsCloseProfile(profiles[0]);
    cmsCloseProfile(profiles[1]);
}

int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    (void)Data;
    (void)Size;

    fuzz_cmsGetSupportedIntents();
    fuzz_cmsCreateTransform();
    fuzz_cmsCreateProofingTransformTHR();
    fuzz_cmsCreateExtendedTransform();
    fuzz_cmsGetSupportedIntentsTHR();
    fuzz_cmsCreateMultiprofileTransformTHR();

    return 0;
}