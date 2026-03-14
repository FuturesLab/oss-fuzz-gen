#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for creating a stage
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0; // Not enough data to create a cmsStage object
    }

    // Extract input and output channel count from the data
    cmsUInt32Number inputChannels = data[0];
    cmsUInt32Number outputChannels = data[1];

    // Create a simple identity matrix for the stage
    cmsFloat64Number identityMatrix[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    // Ensure the number of channels does not exceed the matrix size
    if (inputChannels > 3 || outputChannels > 3) {
        return 0; // Invalid number of channels
    }

    // Create a simple identity matrix stage
    cmsStage *stage = cmsStageAllocMatrix(NULL, inputChannels, outputChannels, (const cmsFloat64Number*)identityMatrix, NULL);
    if (stage == NULL) {
        return 0; // Failed to create the stage
    }

    // Call the function-under-test
    cmsUInt32Number resultInputChannels = cmsStageInputChannels(stage);

    // Clean up
    cmsStageFree(stage);

    return 0;
}