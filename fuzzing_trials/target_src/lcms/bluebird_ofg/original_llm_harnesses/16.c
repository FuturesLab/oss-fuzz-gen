#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Define and initialize variables
    cmsFloat32Number inputFloats[3] = {0.0f, 0.0f, 0.0f};
    cmsFloat32Number outputFloats[3] = {0.0f, 0.0f, 0.0f};
    cmsPipeline *pipeline;

    // Check if the size is sufficient to extract data
    if (size < sizeof(cmsFloat32Number) * 3) {
        return 0;
    }

    // Initialize inputFloats with data from the fuzzer
    for (int i = 0; i < 3; i++) {
        inputFloats[i] = ((cmsFloat32Number *)data)[i];
    }

    // Create a simple pipeline for testing
    pipeline = cmsPipelineAlloc(NULL, 3, 3);
    if (pipeline == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsPipelineEvalFloat(inputFloats, outputFloats, pipeline);

    // Free the allocated pipeline
    cmsPipelineFree(pipeline);

    return 0;
}