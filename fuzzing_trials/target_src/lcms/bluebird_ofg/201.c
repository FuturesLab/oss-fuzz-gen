#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    if (size < 9) {
        // Ensure there is enough data to fill the CLUT and avoid out-of-bounds access
        return 0;
    }

    // Define and initialize the parameters for cmsStageAllocCLutFloatGranular
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number gridPoints[] = {2, 2, 2}; // Example grid points
    cmsUInt32Number inputChannels = 3; // Example input channels
    cmsUInt32Number outputChannels = 3; // Example output channels

    // Allocate memory for the CLUT data
    size_t clutSize = 1;
    for (size_t i = 0; i < inputChannels; i++) {
        clutSize *= gridPoints[i];
    }
    clutSize *= outputChannels;

    cmsFloat32Number *clutData = (cmsFloat32Number *)malloc(clutSize * sizeof(cmsFloat32Number));
    if (clutData == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Fill the CLUT data with non-zero values
    for (size_t i = 0; i < clutSize; i++) {
        clutData[i] = (cmsFloat32Number)(data[i % size] / 255.0f); // Normalize data to [0, 1]
    }

    // Call the function-under-test
    cmsStage *stage = cmsStageAllocCLutFloatGranular(context, gridPoints, inputChannels, outputChannels, clutData);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    free(clutData);
    cmsDeleteContext(context);

    return 0;
}