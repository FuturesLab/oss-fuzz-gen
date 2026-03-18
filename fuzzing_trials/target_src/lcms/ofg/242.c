#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to read a boolean value and some additional data
    if (size < 4) {
        return 0;
    }

    // Initialize variables
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // Assuming 3 input and 3 output channels
    if (pipeline == NULL) {
        return 0;
    }

    // Cast the first byte of data to cmsBool
    cmsBool flag = (cmsBool)(data[0] % 2); // Ensure it is 0 or 1

    // Set the flag using the function-under-test
    cmsPipelineSetSaveAs8bitsFlag(pipeline, flag);

    // Use the rest of the data to add a simple identity transformation to the pipeline
    // This ensures the pipeline is not empty and can be processed
    cmsStage *identityStage = cmsStageAllocIdentity(NULL, 3);
    if (identityStage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_END, identityStage);
    }

    // Optionally, process the pipeline with some dummy data
    float input[3] = {0.0f, 0.0f, 0.0f};
    float output[3];
    cmsPipelineEvalFloat(input, output, pipeline);

    // Clean up
    cmsPipelineFree(pipeline);

    return 0;
}