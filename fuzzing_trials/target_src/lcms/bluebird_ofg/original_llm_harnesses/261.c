#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a dummy cmsPipeline object to use as input
    cmsPipeline *pipeline = cmsPipelineAlloc(context, 3, 3); // Assuming 3 input and 3 output channels
    if (pipeline == NULL) {
        return 0;
    }

    // Add a dummy stage to the pipeline to ensure it's not empty
    cmsStage *stage = cmsStageAllocIdentity(context, 3); // Assuming 3 channels
    if (stage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_END, stage);
    }

    // Call the function-under-test
    cmsPipeline *dup_pipeline = cmsPipelineDup(pipeline);

    // Clean up
    if (dup_pipeline != NULL) {
        cmsPipelineFree(dup_pipeline);
    }
    cmsPipelineFree(pipeline);
    cmsDeleteContext(context);

    return 0;
}