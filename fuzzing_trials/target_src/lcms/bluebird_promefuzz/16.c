#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcms2.h"

#define MAX_INPUT_CHANNELS 16
#define MAX_CLUT_POINTS 256

static cmsBool SamplerFloat(const cmsFloat32Number In[], cmsFloat32Number Out[], void* Cargo) {
    // Dummy sampler function for floating-point CLUT
    return TRUE;
}

static cmsBool Sampler16(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    // Dummy sampler function for 16-bit CLUT
    return TRUE;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    } // Ensure there's at least enough data for nInputs and one clutPoint

    cmsUInt32Number nInputs = Data[0] % MAX_INPUT_CHANNELS;
    if (Size < 1 + nInputs) {
        return 0;
    } // Ensure there's enough data for all clutPoints

    cmsUInt32Number clutPoints[MAX_INPUT_CHANNELS];
    for (cmsUInt32Number i = 0; i < nInputs; i++) {
        clutPoints[i] = (Data[i + 1] % MAX_CLUT_POINTS) + 1;
    }

    cmsContext context = NULL;
    cmsUInt32Number inputChan = nInputs;
    cmsUInt32Number outputChan = (Data[1] % MAX_INPUT_CHANNELS) + 1;

    cmsStage* stage = cmsStageAllocCLutFloatGranular(context, clutPoints, inputChan, outputChan, NULL);
    if (stage != NULL) {
        cmsStageSampleCLutFloat(stage, SamplerFloat, NULL, 0);

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsStageSampleCLut16bit
        cmsStageSampleCLut16bit(stage, Sampler16, NULL, cmsERROR_INTERNAL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        cmsStageFree(stage);
    }

    cmsStage* stage16 = cmsStageAllocCLut16bitGranular(context, clutPoints, inputChan, outputChan, NULL);
    if (stage16 != NULL) {
        cmsStageSampleCLut16bit(stage16, Sampler16, NULL, 0);
        cmsStageFree(stage16);
    }

    cmsSliceSpaceFloat(nInputs, clutPoints, SamplerFloat, NULL);

    return 0;
}