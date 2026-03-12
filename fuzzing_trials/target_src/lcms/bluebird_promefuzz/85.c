#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/lcms/include/lcms2_plugin.h"
#include "lcms2.h"

static cmsContext createDummyContext() {
    // Create a dummy context for testing
    return cmsCreateContext(NULL, NULL);
}

static void fuzz_cmsCreateXYZProfileTHR(cmsContext context) {
    cmsHPROFILE profile = cmsCreateXYZProfileTHR(context);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsCreateTransformTHR(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsUInt32Number)) {
        return;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCreateXYZProfileTHR with cmsCreate_sRGBProfileTHR
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfileTHR(context);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    cmsHPROFILE outputProfile = cmsCreateXYZProfileTHR(context);

    cmsUInt32Number inputFormat = *(cmsUInt32Number*)Data;
    cmsUInt32Number outputFormat = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    cmsHTRANSFORM transform = cmsCreateTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }

    if (inputProfile != NULL) {
        cmsCloseProfile(inputProfile);
    }
    if (outputProfile != NULL) {
        cmsCloseProfile(outputProfile);
    }
}

static void fuzz_cmsGetContextUserData(cmsContext context) {
    void* userData = cmsGetContextUserData(context);
    (void)userData; // Suppress unused variable warning
}

static void fuzz_cmsGetTransformContextID(cmsContext context) {
    cmsHPROFILE profile = cmsCreateXYZProfileTHR(context);
    if (profile != NULL) {
        cmsHTRANSFORM transform = cmsCreateTransformTHR(context, profile, TYPE_RGB_8, profile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
        if (transform != NULL) {
            cmsContext retrievedContext = cmsGetTransformContextID(transform);
            (void)retrievedContext; // Suppress unused variable warning
            cmsDeleteTransform(transform);
        }
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsGetPipelineContextID(cmsContext context) {
    cmsPipeline* pipeline = cmsPipelineAlloc(context, 3, 3);
    if (pipeline != NULL) {
        cmsContext retrievedContext = cmsGetPipelineContextID(pipeline);
        (void)retrievedContext; // Suppress unused variable warning
        cmsPipelineFree(pipeline);
    }
}

static void fuzz__cmsCreateMutex(cmsContext context) {
    void* mutex = _cmsCreateMutex(context);
    if (mutex != NULL) {
        // Dummy cleanup, as _cmsCreateMutex doesn't specify a corresponding destroy function
    }
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    cmsContext context = createDummyContext();
    if (context == NULL) {
        return 0;
    }

    fuzz_cmsCreateXYZProfileTHR(context);
    fuzz_cmsCreateTransformTHR(context, Data, Size);
    fuzz_cmsGetContextUserData(context);
    fuzz_cmsGetTransformContextID(context);
    fuzz_cmsGetPipelineContextID(context);
    fuzz__cmsCreateMutex(context);

    cmsDeleteContext(context);
    return 0;
}