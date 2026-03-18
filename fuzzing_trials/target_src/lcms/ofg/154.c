#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Cast the input data to cmsColorSpaceSignature
    cmsColorSpaceSignature colorSpaceSignature = *(const cmsColorSpaceSignature*)data;

    // Call the function-under-test
    cmsUInt32Number channels = cmsChannelsOf(colorSpaceSignature);

    // Use the result in some way to avoid compiler optimizations
    (void)channels;

    return 0;
}