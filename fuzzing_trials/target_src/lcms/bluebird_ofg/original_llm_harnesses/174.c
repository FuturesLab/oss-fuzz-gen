#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsUInt16Number input[3] = {0, 0, 0};  // Example input array for 3 channels
    cmsUInt16Number output[3] = {0, 0, 0}; // Example output array for 3 channels
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // Allocate a pipeline with 3 input and 3 output channels

    // Check if pipeline allocation was successful
    if (pipeline == NULL) {
        return 0;
    }

    // Populate input array with data from the fuzzer
    for (size_t i = 0; i < 3 && i < size / 2; i++) {
        input[i] = (cmsUInt16Number)((data[i * 2] << 8) | data[i * 2 + 1]);
    }

    // Call the function-under-test
    cmsPipelineEval16(input, output, pipeline);

    // Free the pipeline after use
    cmsPipelineFree(pipeline);

    return 0;
}