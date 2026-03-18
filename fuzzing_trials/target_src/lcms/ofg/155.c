#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    cmsColorSpaceSignature colorSpaceSignature;
    
    // Ensure size is sufficient to read a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Copy data into colorSpaceSignature
    colorSpaceSignature = *(cmsColorSpaceSignature*)data;

    // Call the function-under-test
    cmsUInt32Number channels = cmsChannelsOf(colorSpaceSignature);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)channels;

    return 0;
}