#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Extract a cmsColorSpaceSignature from the input data
    cmsColorSpaceSignature colorSpaceSignature = *(cmsColorSpaceSignature *)data;

    // Call the function under test
    cmsInt32Number channels = cmsChannelsOfColorSpace(colorSpaceSignature);

    // Use the result in some way (optional, for debugging purposes)
    (void)channels; // Suppress unused variable warning

    return 0;
}