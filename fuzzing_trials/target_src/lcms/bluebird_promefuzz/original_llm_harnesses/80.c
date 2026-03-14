// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsStageAllocCLutFloat at cmslut.c:624:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
// cmsStageAllocCLut16bit at cmslut.c:607:21 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsStageAllocToneCurves at cmslut.c:248:21 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static cmsContext create_context() {
    return cmsCreateContext(NULL, NULL);
}

static cmsStage* allocate_clut_float_granular(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 4) return NULL;

    cmsUInt32Number inputChan = Data[0] % 10 + 1; // Limit input channels
    cmsUInt32Number outputChan = Data[1] % 10 + 1; // Limit output channels
    cmsUInt32Number clutPoints[10];
    cmsFloat32Number table[1000]; // Increased size to accommodate larger data

    memset(clutPoints, 0, sizeof(clutPoints));
    memset(table, 0, sizeof(table));

    if (Size < 2 + inputChan) return NULL;

    for (size_t i = 0; i < inputChan && i < 10; i++) {
        clutPoints[i] = Data[2 + i] % 10 + 1;
    }

    size_t tableSize = 1;
    for (size_t i = 0; i < inputChan; i++) {
        tableSize *= clutPoints[i];
    }
    tableSize *= outputChan;

    if (Size > 12 + tableSize * sizeof(cmsFloat32Number)) {
        memcpy(table, Data + 12, tableSize * sizeof(cmsFloat32Number));
    } else {
        return NULL; // Ensure we have enough data for the table
    }

    return cmsStageAllocCLutFloatGranular(context, clutPoints, inputChan, outputChan, table);
}

static cmsStage* allocate_clut_16bit(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 6) return NULL;

    cmsUInt32Number nGridPoints = Data[0] % 10 + 1;
    cmsUInt32Number inputChan = Data[1] % 10 + 1;
    cmsUInt32Number outputChan = Data[2] % 10 + 1;
    cmsUInt16Number table[1000]; // Increased size to accommodate larger data

    memset(table, 0, sizeof(table));

    size_t tableSize = nGridPoints;
    for (size_t i = 0; i < inputChan; i++) {
        tableSize *= nGridPoints;
    }
    tableSize *= outputChan;

    if (Size > 6 + tableSize * sizeof(cmsUInt16Number)) {
        memcpy(table, Data + 6, tableSize * sizeof(cmsUInt16Number));
    } else {
        return NULL; // Ensure we have enough data for the table
    }

    return cmsStageAllocCLut16bit(context, nGridPoints, inputChan, outputChan, table);
}

static cmsStage* allocate_tone_curves(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 4) return NULL;

    cmsUInt32Number nChannels = Data[0] % 10 + 1;
    cmsToneCurve* curves[10];

    for (size_t i = 0; i < nChannels && i < 10; i++) {
        curves[i] = cmsBuildGamma(context, 1.0);
    }

    cmsStage* stage = cmsStageAllocToneCurves(context, nChannels, curves);

    for (size_t i = 0; i < nChannels && i < 10; i++) {
        cmsFreeToneCurve(curves[i]);
    }

    return stage;
}

static cmsStage* allocate_clut_float(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 6) return NULL;

    cmsUInt32Number nGridPoints = Data[0] % 10 + 1;
    cmsUInt32Number inputChan = Data[1] % 10 + 1;
    cmsUInt32Number outputChan = Data[2] % 10 + 1;
    cmsFloat32Number table[1000]; // Increased size to accommodate larger data

    memset(table, 0, sizeof(table));

    size_t tableSize = nGridPoints;
    for (size_t i = 0; i < inputChan; i++) {
        tableSize *= nGridPoints;
    }
    tableSize *= outputChan;

    if (Size > 6 + tableSize * sizeof(cmsFloat32Number)) {
        memcpy(table, Data + 6, tableSize * sizeof(cmsFloat32Number));
    } else {
        return NULL; // Ensure we have enough data for the table
    }

    return cmsStageAllocCLutFloat(context, nGridPoints, inputChan, outputChan, table);
}

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    cmsContext context = create_context();
    if (!context) return 0;

    cmsStage* stage1 = allocate_clut_float_granular(context, Data, Size);
    if (stage1) {
        cmsUInt32Number outputChannels = cmsStageOutputChannels(stage1);
        cmsUInt32Number inputChannels = cmsStageInputChannels(stage1);
        cmsStageFree(stage1);
    }

    cmsStage* stage2 = allocate_clut_16bit(context, Data, Size);
    if (stage2) {
        cmsUInt32Number outputChannels = cmsStageOutputChannels(stage2);
        cmsUInt32Number inputChannels = cmsStageInputChannels(stage2);
        cmsStageFree(stage2);
    }

    cmsStage* stage3 = allocate_tone_curves(context, Data, Size);
    if (stage3) {
        cmsUInt32Number outputChannels = cmsStageOutputChannels(stage3);
        cmsUInt32Number inputChannels = cmsStageInputChannels(stage3);
        cmsStageFree(stage3);
    }

    cmsStage* stage4 = allocate_clut_float(context, Data, Size);
    if (stage4) {
        cmsUInt32Number outputChannels = cmsStageOutputChannels(stage4);
        cmsUInt32Number inputChannels = cmsStageInputChannels(stage4);
        cmsStageFree(stage4);
    }

    cmsDeleteContext(context);
    return 0;
}