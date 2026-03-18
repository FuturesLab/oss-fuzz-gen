#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // Allocate a pipeline with 3 input and 3 output channels
    cmsUInt32Number stageIndex = 0; // Initialize stage index

    // Ensure the pipeline is not NULL
    if (pipeline == NULL) {
        return 0;
    }

    // Add a simple identity stage to the pipeline for testing
    cmsStage *identityStage = cmsStageAllocIdentity(NULL, 3);
    if (identityStage == NULL) {
        cmsPipelineFree(pipeline);
        return 0;
    }
    cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, identityStage);

    // Check if the input data is large enough to be used meaningfully
    if (size < 3 * sizeof(cmsFloat32Number)) {
        cmsPipelineFree(pipeline);
        return 0;
    }

    // Convert input data to float array for the pipeline
    cmsFloat32Number input[3];
    for (int i = 0; i < 3; i++) {
        input[i] = ((cmsFloat32Number)data[i]) / 255.0f; // Normalize data to [0, 1]
    }

    // Prepare an output buffer
    cmsFloat32Number output[3];

    // Evaluate the pipeline with the input data
    cmsPipelineEvalFloat(input, output, pipeline);

    // Call the function-under-test with a valid stage index and a non-null pointer
    cmsStage *retrievedStage;
    cmsBool result = cmsPipelineCheckAndRetreiveStages(pipeline, stageIndex, &retrievedStage);

    // Clean up
    cmsPipelineFree(pipeline);

    return result ? 0 : 1;
}