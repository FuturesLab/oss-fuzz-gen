// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsSliceSpaceFloat at cmslut.c:910:26 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
// cmsStageSampleCLutFloat at cmslut.c:813:19 in lcms2.h
// cmsStageSampleCLut16bit at cmslut.c:747:19 in lcms2.h
// cmsStageAllocCLut16bitGranular at cmslut.c:547:21 in lcms2.h
// cmsStageSampleCLut16bit at cmslut.c:747:19 in lcms2.h
// cmsSliceSpace16 at cmslut.c:879:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

#define MAX_CLUT_POINTS 10

static cmsBool SamplerFloat(cmsFloat32Number In[], cmsFloat32Number Out[], void* Cargo) {
    // Simple sampler function for floating-point values
    return TRUE;
}

static cmsBool Sampler16(cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    // Simple sampler function for 16-bit values
    return TRUE;
}

int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * (3 + MAX_CLUT_POINTS)) {
        return 0; // Not enough data
    }

    cmsUInt32Number nInputs = *((cmsUInt32Number*)Data);
    if (nInputs > MAX_CLUT_POINTS) {
        return 0; // Prevent excessive inputs
    }

    cmsUInt32Number clutPoints[MAX_CLUT_POINTS];
    memcpy(clutPoints, Data + sizeof(cmsUInt32Number), sizeof(cmsUInt32Number) * nInputs);

    // Calculate the total number of elements needed for the table
    size_t totalElements = 1;
    for (cmsUInt32Number i = 0; i < nInputs; i++) {
        totalElements *= clutPoints[i];
    }
    totalElements *= nInputs; // For each input channel

    // Fuzz cmsSliceSpaceFloat
    cmsSliceSpaceFloat(nInputs, clutPoints, SamplerFloat, NULL);

    // Fuzz cmsStageAllocCLutFloatGranular
    cmsContext context = NULL; // Assuming a default context
    cmsFloat32Number* floatTable = (cmsFloat32Number*) malloc(sizeof(cmsFloat32Number) * totalElements); // Correctly sized float table
    if (floatTable) {
        cmsStage* stageFloat = cmsStageAllocCLutFloatGranular(context, clutPoints, nInputs, nInputs, floatTable);
        if (stageFloat) {
            cmsStageSampleCLutFloat(stageFloat, SamplerFloat, NULL, 0);
            cmsStageSampleCLut16bit(stageFloat, Sampler16, NULL, 0);
            free(stageFloat);
        }
        free(floatTable);
    }

    // Fuzz cmsStageAllocCLut16bitGranular
    cmsUInt16Number* table16 = (cmsUInt16Number*) malloc(sizeof(cmsUInt16Number) * totalElements); // Correctly sized 16-bit table
    if (table16) {
        cmsStage* stage16 = cmsStageAllocCLut16bitGranular(context, clutPoints, nInputs, nInputs, table16);
        if (stage16) {
            cmsStageSampleCLut16bit(stage16, Sampler16, NULL, 0);
            free(stage16);
        }
        free(table16);
    }

    // Fuzz cmsSliceSpace16
    cmsSliceSpace16(nInputs, clutPoints, Sampler16, NULL);

    return 0;
}