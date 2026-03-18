// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsStageAllocMatrix at cmslut.c:379:22 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocToneCurves at cmslut.c:248:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocCLutFloat at cmslut.c:624:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

static cmsFloat64Number* generateRandomMatrix(size_t size) {
    cmsFloat64Number* matrix = (cmsFloat64Number*)malloc(size * sizeof(cmsFloat64Number));
    if (!matrix) return NULL;
    for (size_t i = 0; i < size; i++) {
        matrix[i] = (cmsFloat64Number)rand() / RAND_MAX;
    }
    return matrix;
}

static cmsFloat64Number* generateRandomOffset(size_t size) {
    cmsFloat64Number* offset = (cmsFloat64Number*)malloc(size * sizeof(cmsFloat64Number));
    if (!offset) return NULL;
    for (size_t i = 0; i < size; i++) {
        offset[i] = (cmsFloat64Number)rand() / RAND_MAX;
    }
    return offset;
}

static cmsToneCurve* generateRandomToneCurve() {
    // Using cmsBuildGamma to create a simple tone curve
    cmsToneCurve* curve = cmsBuildGamma(NULL, 1.0);
    return curve;
}

static void freeToneCurve(cmsToneCurve* curve) {
    if (curve) {
        cmsFreeToneCurve(curve);
    }
}

int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    cmsContext context = NULL;
    cmsUInt32Number nChannels = Data[0] % 4 + 1; // 1 to 4 channels
    cmsUInt32Number nGridPoints = Data[1] % 10 + 2; // 2 to 11 grid points
    cmsUInt32Number inputChan = Data[2] % 4 + 1;
    cmsUInt32Number outputChan = Data[3] % 4 + 1;

    cmsFloat64Number* matrix = generateRandomMatrix(nChannels * nChannels);
    cmsFloat64Number* offset = generateRandomOffset(nChannels);
    if (!matrix || !offset) goto cleanup;

    cmsStage* stageMatrix = cmsStageAllocMatrix(context, nChannels, nChannels, matrix, offset);
    if (stageMatrix) {
        cmsUInt32Number outChannels = cmsStageOutputChannels(stageMatrix);
        cmsUInt32Number inChannels = cmsStageInputChannels(stageMatrix);
        (void)outChannels;
        (void)inChannels;
        cmsStageFree(stageMatrix);
    }

    cmsStage* stageIdentity = cmsStageAllocIdentity(context, nChannels);
    if (stageIdentity) {
        cmsUInt32Number outChannels = cmsStageOutputChannels(stageIdentity);
        cmsUInt32Number inChannels = cmsStageInputChannels(stageIdentity);
        (void)outChannels;
        (void)inChannels;
        cmsStageFree(stageIdentity);
    }

    cmsToneCurve* curves[4];
    for (cmsUInt32Number i = 0; i < nChannels; i++) {
        curves[i] = generateRandomToneCurve();
    }

    cmsStage* stageToneCurves = cmsStageAllocToneCurves(context, nChannels, curves);
    if (stageToneCurves) {
        cmsUInt32Number outChannels = cmsStageOutputChannels(stageToneCurves);
        cmsUInt32Number inChannels = cmsStageInputChannels(stageToneCurves);
        (void)outChannels;
        (void)inChannels;
        cmsStageFree(stageToneCurves);
    }

    size_t tableSize = 1;
    for (cmsUInt32Number i = 0; i < inputChan; i++) {
        tableSize *= nGridPoints;
    }
    tableSize *= outputChan;

    cmsFloat32Number* table = (cmsFloat32Number*)malloc(tableSize * sizeof(cmsFloat32Number));
    if (!table) goto cleanup;
    for (size_t i = 0; i < tableSize; i++) {
        table[i] = (cmsFloat32Number)rand() / RAND_MAX;
    }

    cmsStage* stageCLut = cmsStageAllocCLutFloat(context, nGridPoints, inputChan, outputChan, table);
    if (stageCLut) {
        cmsUInt32Number outChannels = cmsStageOutputChannels(stageCLut);
        cmsUInt32Number inChannels = cmsStageInputChannels(stageCLut);
        (void)outChannels;
        (void)inChannels;
        cmsStageFree(stageCLut);
    }

cleanup:
    if (matrix) free(matrix);
    if (offset) free(offset);
    if (table) free(table);
    for (cmsUInt32Number i = 0; i < nChannels; i++) {
        freeToneCurve(curves[i]);
    }

    return 0;
}