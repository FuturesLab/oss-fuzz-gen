// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
// cmsDoTransformLineStride at cmsxform.c:229:16 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// _cmsGetTransformFormattersFloat at cmsxform.c:772:16 in lcms2_plugin.h
// _cmsGetTransformFormatters16 at cmsxform.c:765:16 in lcms2_plugin.h
// _cmsGetTransformWorker at cmsxform.c:787:28 in lcms2_plugin.h
// cmsCreateTransform at cmsxform.c:1355:32 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
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
#include "lcms2_plugin.h"

static cmsHPROFILE createDummyProfile() {
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    return profile;
}

static void fuzz_cmsDoTransformLineStride(cmsHTRANSFORM transform, const uint8_t *data, size_t size) {
    if (size < 8) return;

    const void *inputBuffer = data;
    void *outputBuffer = malloc(size);
    if (!outputBuffer) return;

    cmsUInt32Number pixelsPerLine = size / 8;
    cmsUInt32Number lineCount = 1;
    cmsUInt32Number bytesPerLineIn = size;
    cmsUInt32Number bytesPerLineOut = size;
    cmsUInt32Number bytesPerPlaneIn = size;
    cmsUInt32Number bytesPerPlaneOut = size;

    cmsDoTransformLineStride(transform, inputBuffer, outputBuffer, pixelsPerLine, lineCount,
                             bytesPerLineIn, bytesPerLineOut, bytesPerPlaneIn, bytesPerPlaneOut);

    free(outputBuffer);
}

static void fuzz_cmsDoTransform(cmsHTRANSFORM transform, const uint8_t *data, size_t size) {
    if (size < 4) return;

    const void *inputBuffer = data;
    void *outputBuffer = malloc(size);
    if (!outputBuffer) return;

    cmsDoTransform(transform, inputBuffer, outputBuffer, size / 4);

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
    if (size < 8) return NULL;

    cmsHPROFILE inputProfile = createDummyProfile();
    cmsHPROFILE outputProfile = createDummyProfile();
    if (!inputProfile || !outputProfile) return NULL;

    cmsUInt32Number inputFormat = *(cmsUInt32Number *)data;
    cmsUInt32Number outputFormat = *(cmsUInt32Number *)(data + 4);
    cmsUInt32Number intent = 0;
    cmsUInt32Number flags = 0;

    cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return transform;
}

int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    cmsHTRANSFORM transform = fuzz_cmsCreateTransform(Data, Size);
    if (!transform) return 0;

    fuzz_cmsDoTransformLineStride(transform, Data, Size);
    fuzz_cmsDoTransform(transform, Data, Size);

    struct _cmstransform_struct *transformStruct = (struct _cmstransform_struct *)transform;
    fuzz__cmsGetTransformFormattersFloat(transformStruct);
    fuzz__cmsGetTransformFormatters16(transformStruct);
    fuzz__cmsGetTransformWorker(transformStruct);

    cmsDeleteTransform(transform);
    return 0;
}