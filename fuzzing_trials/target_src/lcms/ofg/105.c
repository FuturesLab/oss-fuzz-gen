#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Extract a cmsColorSpaceSignature from the input data
    cmsColorSpaceSignature colorSpaceSignature = *(cmsColorSpaceSignature*)data;

    // Call the function-under-test
    cmsInt32Number channels = cmsChannelsOfColorSpace(colorSpaceSignature);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)channels; // In a real test, you might want to check the result or use it further

    return 0;
}