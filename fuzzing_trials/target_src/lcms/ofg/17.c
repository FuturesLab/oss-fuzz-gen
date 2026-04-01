#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Define the number of input and output channels
    const int numChannels = 3;

    // Allocate memory for input and output arrays
    cmsFloat32Number input[numChannels];
    cmsFloat32Number output[numChannels];

    // Initialize input array with data from the fuzzer
    for (int i = 0; i < numChannels; i++) {
        if (i * sizeof(cmsFloat32Number) < size) {
            input[i] = ((cmsFloat32Number *)data)[i];
        } else {
            input[i] = 0.0f; // Default value if not enough data
        }
    }

    // Create a dummy cmsPipeline for testing
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, numChannels, numChannels);
    if (pipeline == NULL) {
        return 0; // Exit if pipeline allocation fails
    }

    // Call the function-under-test
    cmsPipelineEvalFloat(input, output, pipeline);

    // Free the allocated pipeline
    cmsPipelineFree(pipeline);

    return 0;
}