#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

#define MAX_CLUT_POINTS 16
#define MAX_INPUT_CHANNELS 16
#define MAX_OUTPUT_CHANNELS 16

static cmsBool SampleFloatFn(const cmsFloat32Number In[], cmsFloat32Number Out[], void* Cargo) {
    // Simple sampler function for floating point
    for (int i = 0; i < MAX_OUTPUT_CHANNELS; i++) {
        Out[i] = In[i % MAX_INPUT_CHANNELS];
    }
    return TRUE;
}

static cmsBool Sample16Fn(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    // Simple sampler function for 16-bit
    for (int i = 0; i < MAX_OUTPUT_CHANNELS; i++) {
        Out[i] = In[i % MAX_INPUT_CHANNELS];
    }
    return TRUE;
}

int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * MAX_CLUT_POINTS + sizeof(cmsFloat32Number)) return 0;

    cmsUInt32Number clutPoints[MAX_CLUT_POINTS];
    memcpy(clutPoints, Data, sizeof(cmsUInt32Number) * MAX_CLUT_POINTS);
    Data += sizeof(cmsUInt32Number) * MAX_CLUT_POINTS;
    Size -= sizeof(cmsUInt32Number) * MAX_CLUT_POINTS;

    cmsFloat32Number table[MAX_CLUT_POINTS * MAX_INPUT_CHANNELS * MAX_OUTPUT_CHANNELS];
    if (Size < sizeof(cmsFloat32Number) * MAX_CLUT_POINTS * MAX_INPUT_CHANNELS * MAX_OUTPUT_CHANNELS) return 0;
    memcpy(table, Data, sizeof(cmsFloat32Number) * MAX_CLUT_POINTS * MAX_INPUT_CHANNELS * MAX_OUTPUT_CHANNELS);

    cmsContext context = NULL; // NULL context for default
    cmsStage* stage = cmsStageAllocCLutFloatGranular(context, clutPoints, MAX_INPUT_CHANNELS, MAX_OUTPUT_CHANNELS, table);
    if (stage) {
        cmsStageSampleCLutFloat(stage, SampleFloatFn, NULL, 0);
        cmsStageFree(stage);
    }

    stage = cmsStageAllocCLut16bitGranular(context, clutPoints, MAX_INPUT_CHANNELS, MAX_OUTPUT_CHANNELS, (const cmsUInt16Number*)table);
    if (stage) {
        cmsStageSampleCLut16bit(stage, Sample16Fn, NULL, 0);
        cmsStageFree(stage);
    }

    cmsSliceSpaceFloat(MAX_INPUT_CHANNELS, clutPoints, SampleFloatFn, NULL);
    cmsSliceSpace16(MAX_INPUT_CHANNELS, clutPoints, Sample16Fn, NULL);

    return 0;
}