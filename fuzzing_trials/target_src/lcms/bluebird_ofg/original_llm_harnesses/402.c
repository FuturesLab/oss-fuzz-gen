#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nInputChannels = 3; // Example value, adjust as needed
    cmsUInt32Number nOutputChannels = 3; // Example value, adjust as needed
    cmsUInt32Number gridPoints = 2; // Example value, adjust as needed

    // Ensure there is enough data to fill the LUT
    if (size < nInputChannels * nOutputChannels * gridPoints * sizeof(cmsUInt16Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    const cmsUInt16Number *table = (const cmsUInt16Number *)data;

    cmsStage *stage = cmsStageAllocCLut16bit(context, nInputChannels, nOutputChannels, gridPoints, table);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    cmsDeleteContext(context);

    return 0;
}