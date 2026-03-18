#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to safely cast to a cmsStage pointer
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Cast the input data to a cmsStage pointer
    const cmsStage *stage = (const cmsStage *)data;

    // Call the function-under-test
    cmsUInt32Number inputChannels = cmsStageInputChannels(stage);

    // Use the result in some way to avoid compiler optimizations
    if (inputChannels == 0) {
        return 0;
    }

    return 0;
}