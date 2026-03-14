#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"

static cmsHPROFILE createDummyProfile() {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCreate_sRGBProfile with cmsCreateXYZProfile
    cmsHPROFILE profile = cmsCreateXYZProfile();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return profile;
}

static void fuzz_cmsDoTransformLineStride(cmsHTRANSFORM transform, const uint8_t *data, size_t size) {
    if (size < 8) {
        return;
    }

    const void *inputBuffer = data;
    void *outputBuffer = malloc(size);
    if (!outputBuffer) {
        return;
    }

    cmsUInt32Number pixelsPerLine = size / 8;
    cmsUInt32Number lineCount = 1;
    cmsUInt32Number bytesPerLineIn = size;
    cmsUInt32Number bytesPerLineOut = size;
    cmsUInt32Number bytesPerPlaneIn = size;
    cmsUInt32Number bytesPerPlaneOut = size;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 8 of cmsDoTransformLineStride

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 6 of cmsDoTransformLineStride

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsDoTransformLineStride
    cmsDoTransformLineStride(transform, inputBuffer, outputBuffer, cmsD50X, lineCount, bytesPerLineIn, cmsERROR_ALREADY_DEFINED, bytesPerPlaneIn, LCMS_USED_AS_PROOF);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    free(outputBuffer);
}

static void fuzz_cmsDoTransform(cmsHTRANSFORM transform, const uint8_t *data, size_t size) {
    if (size < 4) {
        return;
    }

    const void *inputBuffer = data;
    void *outputBuffer = malloc(size);
    if (!outputBuffer) {
        return;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsDoTransform
    char zipbpcfd[1024] = "rfxqm";

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsDoTransform

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsDoTransform
    char oklewgbh[1024] = "duogf";
    cmsDoTransform(transform, oklewgbh, zipbpcfd, cmsSPOT_PRINTER_DEFAULT);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    free(outputBuffer);
}

static void fuzz__cmsGetTransformFormattersFloat(struct _cmstransform_struct *transformStruct) {
    cmsFormatterFloat fromInput = NULL;
    cmsFormatterFloat toOutput = NULL;

    _cmsGetTransformFormattersFloat(transformStruct, &fromInput, &toOutput);
}

static void fuzz__cmsGetTransformFormatters16(struct _cmstransform_struct *transformStruct) {
    cmsFormatter16 fromInput = NULL;
    cmsFormatter16 toOutput = NULL;

    _cmsGetTransformFormatters16(transformStruct, &fromInput, &toOutput);
}

static void fuzz__cmsGetTransformWorker(struct _cmstransform_struct *transformStruct) {
    _cmsGetTransformWorker(transformStruct);
}

static cmsHTRANSFORM fuzz_cmsCreateTransform(const uint8_t *data, size_t size) {
    if (size < 8) {
        return NULL;
    }

    cmsHPROFILE inputProfile = createDummyProfile();
    cmsHPROFILE outputProfile = createDummyProfile();
    if (!inputProfile || !outputProfile) {
        return NULL;
    }

    cmsUInt32Number inputFormat = *(cmsUInt32Number *)data;
    cmsUInt32Number outputFormat = *(cmsUInt32Number *)(data + 4);
    cmsUInt32Number intent = 0;
    cmsUInt32Number flags = 0;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of cmsCreateTransform

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of cmsCreateTransform
    cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, inputFormat, outputProfile, outputFormat, AVG_SURROUND, INTENT_PRESERVE_K_ONLY_PERCEPTUAL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR




    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsIsMatrixShaper

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIsMatrixShaper with cmsCloseProfile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
    cmsMD5computeID(inputProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    cmsCloseProfile(outputProfile);

    return transform;
}

int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    cmsHTRANSFORM transform = fuzz_cmsCreateTransform(Data, Size);
    if (!transform) {
        return 0;
    }

    fuzz_cmsDoTransformLineStride(transform, Data, Size);
    fuzz_cmsDoTransform(transform, Data, Size);

    struct _cmstransform_struct *transformStruct = (struct _cmstransform_struct *)transform;
    fuzz__cmsGetTransformFormattersFloat(transformStruct);
    fuzz__cmsGetTransformFormatters16(transformStruct);
    fuzz__cmsGetTransformWorker(transformStruct);

    cmsDeleteTransform(transform);
    return 0;
}