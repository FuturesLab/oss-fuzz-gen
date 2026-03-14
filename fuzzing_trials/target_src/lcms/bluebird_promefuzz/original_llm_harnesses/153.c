// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineEval16 at cmslut.c:1447:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineCat at cmslut.c:1612:20 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static cmsPipeline* create_random_pipeline() {
    cmsPipeline* pipeline = cmsPipelineAlloc(NULL, 3, 3);
    if (!pipeline) return NULL;

    // Create a dummy stage
    cmsStage* stage = cmsStageAllocIdentity(NULL, 3);
    if (!stage) {
        cmsPipelineFree(pipeline);
        return NULL;
    }

    // Insert the stage into the pipeline
    if (!cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage)) {
        cmsStageFree(stage);
        cmsPipelineFree(pipeline);
        return NULL;
    }

    return pipeline;
}

static void fuzz_cmsPipelineInsertStage(const uint8_t *Data, size_t Size) {
    cmsPipeline* pipeline = create_random_pipeline();
    if (!pipeline) return;

    cmsStage* stage = cmsStageAllocIdentity(NULL, 3);
    if (!stage) {
        cmsPipelineFree(pipeline);
        return;
    }

    cmsStageLoc loc = (Size > 0 && Data[0] % 2 == 0) ? cmsAT_BEGIN : cmsAT_END;
    cmsPipelineInsertStage(pipeline, loc, stage);

    cmsPipelineFree(pipeline);
}

static void fuzz_cmsPipelineEval16(const uint8_t *Data, size_t Size) {
    cmsPipeline* pipeline = create_random_pipeline();
    if (!pipeline) return;

    cmsUInt16Number In[3] = {0};
    cmsUInt16Number Out[3] = {0};

    if (Size >= sizeof(In)) {
        memcpy(In, Data, sizeof(In));
    }

    cmsPipelineEval16(In, Out, pipeline);

    cmsPipelineFree(pipeline);
}

static void fuzz_cmsPipelineSetSaveAs8bitsFlag(const uint8_t *Data, size_t Size) {
    cmsPipeline* pipeline = create_random_pipeline();
    if (!pipeline) return;

    cmsBool flag = (Size > 0 && Data[0] % 2 == 0) ? TRUE : FALSE;
    cmsPipelineSetSaveAs8bitsFlag(pipeline, flag);

    cmsPipelineFree(pipeline);
}

static void fuzz_cmsPipelineCat(const uint8_t *Data, size_t Size) {
    cmsPipeline* l1 = create_random_pipeline();
    cmsPipeline* l2 = create_random_pipeline();
    if (!l1 || !l2) {
        cmsPipelineFree(l1);
        cmsPipelineFree(l2);
        return;
    }

    cmsPipelineCat(l1, l2);

    cmsPipelineFree(l1);
    cmsPipelineFree(l2);
}

static void fuzz_cmsPipelineDup(const uint8_t *Data, size_t Size) {
    cmsPipeline* pipeline = create_random_pipeline();
    if (!pipeline) return;

    cmsPipeline* dup = cmsPipelineDup(pipeline);
    if (dup) {
        cmsPipelineFree(dup);
    }

    cmsPipelineFree(pipeline);
}

int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    fuzz_cmsPipelineInsertStage(Data, Size);
    fuzz_cmsPipelineEval16(Data, Size);
    fuzz_cmsPipelineSetSaveAs8bitsFlag(Data, Size);
    fuzz_cmsPipelineCat(Data, Size);
    fuzz_cmsPipelineDup(Data, Size);
    return 0;
}