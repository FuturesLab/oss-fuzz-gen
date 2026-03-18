#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number gridPoints[] = { 2, 2, 2 }; // Example grid points
    cmsUInt32Number inputChannels = 3; // Example input channel count
    cmsUInt32Number outputChannels = 3; // Example output channel count
    cmsUInt16Number table[] = { 0, 65535, 32768, 16384, 49152, 8192, 4096, 2048 }; // Example table

    // Ensure enough data for gridPoints and table
    size_t requiredSize = sizeof(gridPoints) + sizeof(table);
    if (size < requiredSize) {
        return 0;
    }

    // Allocate memory for the table based on the input data
    cmsUInt16Number *dynamicTable = (cmsUInt16Number *)malloc(sizeof(cmsUInt16Number) * (size / sizeof(cmsUInt16Number)));
    if (dynamicTable == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Copy data into the dynamic table
    for (size_t i = 0; i < size / sizeof(cmsUInt16Number); i++) {
        dynamicTable[i] = ((cmsUInt16Number *)data)[i];
    }

    cmsStage *stage = cmsStageAllocCLut16bitGranular(context, gridPoints, inputChannels, outputChannels, dynamicTable);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    free(dynamicTable);
    cmsDeleteContext(context);

    return 0;
}