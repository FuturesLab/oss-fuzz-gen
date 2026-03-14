#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_409(const uint8_t *data, size_t size) {
    cmsPipeline *pipeline = NULL;
    cmsStage *stage = NULL;

    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a cmsPipeline object with at least one stage to avoid NULL
    pipeline = cmsPipelineAlloc(contextID, 3, 3);
    if (pipeline == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Add a dummy stage to the pipeline
    cmsStage *identityStage = cmsStageAllocIdentity(contextID, 3);
    if (identityStage == NULL) {
        cmsPipelineFree(pipeline);
        cmsDeleteContext(contextID);
        return 0;
    }
    cmsPipelineInsertStage(pipeline, cmsAT_END, identityStage);

    // Call the function-under-test
    stage = cmsPipelineGetPtrToFirstStage(pipeline);

    // Clean up
    cmsPipelineFree(pipeline);
    cmsDeleteContext(contextID);

    return 0;
}