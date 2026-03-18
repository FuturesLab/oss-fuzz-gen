#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to perform operations
    if (size < sizeof(float) * 9) {
        return 0;
    }

    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3);
    if (pipeline == NULL) {
        return 0;
    }

    // Use the input data to create a matrix for the stage
    const float *matrixData = (const float *)data;
    cmsStage *stage = cmsStageAllocMatrix(NULL, 3, 3, matrixData, NULL);
    if (stage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_END, stage);
    }

    // Call the function-under-test
    cmsStage *lastStage = cmsPipelineGetPtrToLastStage(pipeline);

    // Use the lastStage in some way to ensure it is not optimized away
    if (lastStage != NULL) {
        // For example, retrieve some information from it
        int inputChannels = cmsStageInputChannels(lastStage);
        int outputChannels = cmsStageOutputChannels(lastStage);
        (void)inputChannels;
        (void)outputChannels;
    }

    // Clean up
    cmsPipelineFree(pipeline);

    return 0;
}