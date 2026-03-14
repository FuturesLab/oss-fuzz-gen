#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

// Fuzzing harness for cmsGetPipelineContextID
int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Initialize a cmsPipeline object
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // 3 input and 3 output channels

    // Ensure the pipeline is not NULL
    if (pipeline == NULL) {
        return 0;
    }

    // Create an identity matrix for testing
    const double identityMatrix[9] = { 1.0, 0.0, 0.0,
                                       0.0, 1.0, 0.0,
                                       0.0, 0.0, 1.0 };

    // Add a simple identity matrix to the pipeline for testing
    cmsStage *identityStage = cmsStageAllocMatrix(NULL, 3, 3, identityMatrix, NULL);
    if (identityStage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, identityStage);
    }

    // Call the function-under-test
    cmsContext contextID = cmsGetPipelineContextID(pipeline);

    // Clean up
    cmsPipelineFree(pipeline);

    return 0;
}