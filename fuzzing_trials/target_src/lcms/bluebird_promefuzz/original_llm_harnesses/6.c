// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineInputChannels at cmslut.c:1413:27 in lcms2.h
// cmsPipelineOutputChannels at cmslut.c:1419:27 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
// cmsPipelineStageCount at cmslut.c:1661:27 in lcms2.h
// cmsPipelineCheckAndRetreiveStages at cmslut.c:110:20 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "lcms2.h"

static cmsContext createDummyContext() {
    return cmsCreateContext(NULL, NULL);
}

static void cleanupContext(cmsContext context) {
    cmsDeleteContext(context);
}

static void fuzz_cmsPipelineFunctions(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    cmsUInt32Number inputChannels = Data[0];
    cmsUInt32Number outputChannels = Data[1];

    // Test cmsPipelineAlloc
    cmsPipeline* pipeline = cmsPipelineAlloc(context, inputChannels, outputChannels);
    if (pipeline) {
        // Test cmsPipelineInputChannels
        cmsUInt32Number inChannels = cmsPipelineInputChannels(pipeline);

        // Test cmsPipelineOutputChannels
        cmsUInt32Number outChannels = cmsPipelineOutputChannels(pipeline);

        // Test cmsPipelineDup
        cmsPipeline* pipelineDup = cmsPipelineDup(pipeline);

        // Test cmsPipelineStageCount
        cmsUInt32Number stageCount = cmsPipelineStageCount(pipeline);

        // Test cmsPipelineCheckAndRetreiveStages with dummy arguments
        cmsBool result = cmsPipelineCheckAndRetreiveStages(pipeline, 0);

        // Cleanup duplicated pipeline
        if (pipelineDup) {
            cmsPipelineFree(pipelineDup);
        }

        // Cleanup original pipeline
        cmsPipelineFree(pipeline);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    cmsContext context = createDummyContext();
    if (context) {
        fuzz_cmsPipelineFunctions(context, Data, Size);
        cleanupContext(context);
    }
    return 0;
}