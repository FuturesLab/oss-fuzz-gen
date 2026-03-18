// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
// cmsPipelineCat at cmslut.c:1612:20 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineCheckAndRetreiveStages at cmslut.c:110:20 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

static cmsPipeline* create_dummy_pipeline() {
    return cmsPipelineAlloc(NULL, 3, 3); // Allocating a pipeline with 3 input and 3 output channels
}

static cmsStage* create_dummy_stage() {
    return cmsStageAllocIdentity(NULL, 3); // Allocating an identity stage with 3 channels
}

static void cleanup_pipeline(cmsPipeline* pipeline) {
    if (pipeline) {
        cmsPipelineFree(pipeline);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    cmsPipeline* pipeline1 = create_dummy_pipeline();
    cmsPipeline* pipeline2 = create_dummy_pipeline();
    cmsStage* stage = create_dummy_stage();

    if (!pipeline1 || !pipeline2 || !stage) {
        cleanup_pipeline(pipeline1);
        cleanup_pipeline(pipeline2);
        cmsStageFree(stage);
        return 0;
    }

    // Fuzz cmsPipelineInsertStage
    cmsStageLoc loc = (cmsStageLoc)(Data[0] % 2); // Randomly choose loc as 0 or 1
    cmsPipelineInsertStage(pipeline1, loc, stage);

    // Fuzz cmsPipelineSetSaveAs8bitsFlag
    cmsBool flag = (cmsBool)(Data[0] % 2);
    cmsPipelineSetSaveAs8bitsFlag(pipeline1, flag);

    // Fuzz cmsPipelineCat
    cmsPipelineCat(pipeline1, pipeline2);

    // Fuzz cmsPipelineDup
    cmsPipeline* dupPipeline = cmsPipelineDup(pipeline1);
    if (dupPipeline) {
        cmsPipelineFree(dupPipeline);
    }

    // Fuzz cmsPipelineCheckAndRetreiveStages
    cmsStage* retrievedStages[1];
    cmsPipelineCheckAndRetreiveStages(pipeline1, 1, retrievedStages);

    // Clean up
    // Note: Do not free the stage here as it is managed by the pipeline after insertion
    cleanup_pipeline(pipeline1);
    cleanup_pipeline(pipeline2);

    return 0;
}