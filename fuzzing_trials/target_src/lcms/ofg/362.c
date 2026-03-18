#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_362(const uint8_t *data, size_t size) {
    // Define and initialize variables
    cmsContext context = (cmsContext)0x1; // Non-null context
    cmsUInt32Number nGridPoints = 2; // Minimum grid points
    cmsUInt32Number inputChannels = 3; // Example input channels
    cmsUInt32Number outputChannels = 3; // Example output channels

    // Ensure the data size is sufficient for the float array
    if (size < inputChannels * outputChannels * nGridPoints * sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Cast the input data to a float array
    const cmsFloat32Number* floatArray = (const cmsFloat32Number*)data;

    // Call the function-under-test
    cmsStage* stage = cmsStageAllocCLutFloat(context, nGridPoints, inputChannels, outputChannels, floatArray);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }

    return 0;
}