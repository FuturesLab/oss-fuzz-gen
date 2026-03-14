#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_405(const uint8_t *data, size_t size) {
    // Initialize the memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create two cmsPipeline objects
    cmsPipeline *pipeline1 = cmsPipelineAlloc(context, 3, 3);
    cmsPipeline *pipeline2 = cmsPipelineAlloc(context, 3, 3);

    // Check if the pipelines were created successfully
    if (pipeline1 == NULL || pipeline2 == NULL) {
        if (pipeline1 != NULL) cmsPipelineFree(pipeline1);
        if (pipeline2 != NULL) cmsPipelineFree(pipeline2);
        cmsDeleteContext(context);
        return 0;
    }

    // Create some dummy stages to add to the pipelines
    cmsStage *stage1 = cmsStageAllocIdentity(context, 3);
    cmsStage *stage2 = cmsStageAllocIdentity(context, 3);

    // Add stages to the pipelines
    if (stage1 != NULL) cmsPipelineInsertStage(pipeline1, cmsAT_END, stage1);
    if (stage2 != NULL) cmsPipelineInsertStage(pipeline2, cmsAT_END, stage2);

    // Fuzz the cmsPipelineCat function
    cmsBool result = cmsPipelineCat(pipeline1, pipeline2);

    // Free resources
    cmsPipelineFree(pipeline1);
    cmsPipelineFree(pipeline2);
    cmsDeleteContext(context);

    return 0;
}