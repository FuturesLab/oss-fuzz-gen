#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_335(const uint8_t *data, size_t size) {
    cmsContext context = (cmsContext)data; // Cast data to cmsContext
    cmsUInt32Number inputChannels = 3; // Example value for input channels
    cmsUInt32Number outputChannels = 3; // Example value for output channels

    // Ensure that the size is sufficient for the context
    if (size < sizeof(cmsContext)) {
        return 0;
    }

    // Call the function-under-test
    cmsPipeline *pipeline = cmsPipelineAlloc(context, inputChannels, outputChannels);

    // Clean up if allocation was successful
    if (pipeline != NULL) {
        cmsPipelineFree(pipeline);
    }

    return 0;
}