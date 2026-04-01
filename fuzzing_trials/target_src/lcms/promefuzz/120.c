// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineEvalFloat at cmslut.c:1455:16 in lcms2.h
// cmsPipelineEvalReverseFloat at cmslut.c:1753:19 in lcms2.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
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
#include <lcms2.h>

static cmsPipeline* create_dummy_pipeline(cmsUInt32Number inputChannels, cmsUInt32Number outputChannels) {
    cmsPipeline* pipeline = cmsPipelineAlloc(NULL, inputChannels, outputChannels);
    if (!pipeline) return NULL;

    // Add a dummy stage to the pipeline
    cmsStage* stage = cmsStageAllocIdentity(NULL, inputChannels);
    if (!stage) {
        cmsPipelineFree(pipeline);
        return NULL;
    }

    if (!cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage)) {
        cmsStageFree(stage);
        cmsPipelineFree(pipeline);
        return NULL;
    }

    return pipeline;
}

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat32Number) * 6) return 0;

    cmsFloat32Number In[3];
    cmsFloat32Number Out[3];
    cmsFloat32Number Target[3];
    cmsFloat32Number Result[3];
    cmsFloat32Number Hint[3];

    memcpy(In, Data, sizeof(cmsFloat32Number) * 3);
    memcpy(Target, Data + sizeof(cmsFloat32Number) * 3, sizeof(cmsFloat32Number) * 3);

    cmsPipeline* lut = create_dummy_pipeline(3, 3);
    if (!lut) return 0;

    cmsPipelineEvalFloat(In, Out, lut);

    cmsBool reverseSuccess = cmsPipelineEvalReverseFloat(Target, Result, Hint, lut);

    cmsBool oldFlag = cmsPipelineSetSaveAs8bitsFlag(lut, TRUE);
    cmsBool newFlag = cmsPipelineSetSaveAs8bitsFlag(lut, oldFlag);

    cmsPipeline* dupLut = cmsPipelineDup(lut);
    if (dupLut) {
        cmsPipelineFree(dupLut);
    }

    cmsPipelineFree(lut);

    return 0;
}