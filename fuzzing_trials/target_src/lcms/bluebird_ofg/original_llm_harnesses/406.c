#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_406(const uint8_t *data, size_t size) {
    cmsPipeline *pipeline1 = NULL;
    cmsPipeline *pipeline2 = NULL;
    cmsContext context = cmsCreateContext(NULL, NULL);

    if (context == NULL || size < sizeof(float) * 3) {
        return 0;
    }

    // Create two pipelines with a single stage each for testing
    pipeline1 = cmsPipelineAlloc(context, 3, 3);
    pipeline2 = cmsPipelineAlloc(context, 3, 3);

    if (pipeline1 == NULL || pipeline2 == NULL) {
        cmsPipelineFree(pipeline1);
        cmsPipelineFree(pipeline2);
        cmsDeleteContext(context);
        return 0;
    }

    // Use the input data to create a transformation stage
    float *matrix = (float *)data;
    cmsStage *stage1 = cmsStageAllocMatrix(context, 3, 3, matrix, NULL);
    cmsStage *stage2 = cmsStageAllocIdentity(context, 3);

    if (stage1 == NULL || stage2 == NULL) {
        cmsPipelineFree(pipeline1);
        cmsPipelineFree(pipeline2);
        cmsDeleteContext(context);
        return 0;
    }

    cmsPipelineInsertStage(pipeline1, cmsAT_BEGIN, stage1);
    cmsPipelineInsertStage(pipeline2, cmsAT_BEGIN, stage2);

    // Fuzz the function-under-test
    cmsBool result = cmsPipelineCat(pipeline1, pipeline2);

    // Clean up
    cmsPipelineFree(pipeline1);
    cmsPipelineFree(pipeline2);
    cmsDeleteContext(context);

    return 0;
}