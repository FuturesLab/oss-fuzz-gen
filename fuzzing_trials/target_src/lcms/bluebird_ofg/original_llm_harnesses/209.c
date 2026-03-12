#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_209(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a new pipeline with a given input and output channel count
    cmsPipeline *pipeline = cmsPipelineAlloc(contextID, 3, 3);

    // Ensure the pipeline is not NULL
    if (pipeline == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Add a simple identity stage to the pipeline
    cmsStage *identityStage = cmsStageAllocIdentity(contextID, 3);
    if (identityStage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_END, identityStage);
    }

    // Call the function-under-test
    cmsStage *lastStage = cmsPipelineGetPtrToLastStage(pipeline);

    // Check if the last stage is not NULL
    if (lastStage != NULL) {
        // Optionally perform operations on the last stage
    }

    // Clean up
    cmsPipelineFree(pipeline);
    cmsDeleteContext(contextID);

    return 0;
}