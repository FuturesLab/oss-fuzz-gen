#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    tjhandle handle = tjInitTransform();
    if (handle == nullptr) {
        return 0;
    }

    // Allocate memory for the destination buffer
    unsigned char *dstBuffer = nullptr;
    unsigned long dstSize = 0;

    // Initialize a tjtransform structure
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform));

    // Set some options for the transformation
    int options = 0;

    // Call tjTransform with the provided data
    int result = tjTransform(handle, data, size, 1, &dstBuffer, &dstSize, &transform, options);

    // Clean up
    if (dstBuffer != nullptr) {
        tjFree(dstBuffer);
    }
    tjDestroy(handle);

    return result;
}