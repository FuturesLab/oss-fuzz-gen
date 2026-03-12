#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsContext context = (cmsContext)data; // Cast data to cmsContext
    cmsUInt32Number nChannels = 3; // Example number of channels, not zero

    // Call the function-under-test
    cmsStage *stage = cmsStageAllocIdentity(context, nChannels);

    // Perform cleanup if necessary
    if (stage != NULL) {
        cmsStageFree(stage);
    }

    return 0;
}