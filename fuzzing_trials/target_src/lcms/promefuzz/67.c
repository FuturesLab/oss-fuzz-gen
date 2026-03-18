// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsPipelineGetPtrToFirstStage at cmslut.c:1646:21 in lcms2.h
// cmsPipelineGetPtrToLastStage at cmslut.c:1651:21 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageData at cmslut.c:1233:17 in lcms2.h
// cmsPipelineUnlinkStage at cmslut.c:1555:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsPipeline* createDummyPipeline() {
    cmsPipeline* pipeline = cmsPipelineAlloc(NULL, 3, 3);
    return pipeline;
}

static cmsStage* createDummyStage() {
    cmsStage* stage = cmsStageAllocIdentity(NULL, 3);
    return stage;
}

static void cleanupPipeline(cmsPipeline* pipeline) {
    cmsPipelineFree(pipeline);
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsPipeline* pipeline = createDummyPipeline();
    if (!pipeline) return 0;

    cmsStage* stage = createDummyStage();
    if (!stage) {
        cmsPipelineFree(pipeline);
        return 0;
    }

    cmsStageLoc loc = (Data[0] % 2) ? cmsAT_BEGIN : cmsAT_END;

    // Test cmsPipelineInsertStage
    cmsBool result = cmsPipelineInsertStage(pipeline, loc, stage);
    if (result) {
        // Test cmsPipelineGetPtrToFirstStage
        cmsStage* firstStage = cmsPipelineGetPtrToFirstStage(pipeline);

        // Test cmsPipelineGetPtrToLastStage
        cmsStage* lastStage = cmsPipelineGetPtrToLastStage(pipeline);

        // Test cmsStageNext
        if (firstStage) {
            cmsStage* nextStage = cmsStageNext(firstStage);
        }

        // Test cmsStageData
        void* stageData = cmsStageData(firstStage);

        // Test cmsPipelineUnlinkStage
        cmsStage* unlinkedStage = NULL;
        cmsPipelineUnlinkStage(pipeline, loc, &unlinkedStage);
        if (unlinkedStage) {
            cmsStageFree(unlinkedStage);
        }
    }

    cleanupPipeline(pipeline);
    return 0;
}