#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Fuzzer entry point
int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Allocate memory for cmsPipeline
    cmsPipeline *pipeline = cmsPipelineAlloc(context, 3, 3);
    if (pipeline == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number inputChannels = cmsPipelineInputChannels(pipeline);

    // Clean up
    cmsPipelineFree(pipeline);
    cmsDeleteContext(context);

    return 0;
}