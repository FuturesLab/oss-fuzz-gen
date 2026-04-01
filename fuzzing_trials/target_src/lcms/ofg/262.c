#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for the operations
    if (size < sizeof(float) * 3) {
        return 0; // Not enough data to proceed
    }

    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // Allocate a pipeline with 3 input and 3 output channels

    if (pipeline == NULL) {
        return 0; // If allocation fails, exit early
    }

    // Simulate adding some elements to the pipeline
    cmsStage *identityStage = cmsStageAllocIdentity(NULL, 3); // Create an identity stage
    if (identityStage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_END, identityStage);
    }

    // Use the input data to create a sample point for testing
    const float *inputSample = (const float *)data;

    // Call the function-under-test
    cmsPipelineEvalFloat(inputSample, inputSample, pipeline);

    // Duplicate the pipeline to test duplication functionality
    cmsPipeline *dupPipeline = cmsPipelineDup(pipeline);

    // Clean up
    if (dupPipeline != NULL) {
        cmsPipelineFree(dupPipeline);
    }
    cmsPipelineFree(pipeline);

    return 0;
}