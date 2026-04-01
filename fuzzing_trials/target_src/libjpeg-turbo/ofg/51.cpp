#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize variables
    tjhandle handle = tjInitTransform();
    if (!handle) {
        return 0;
    }

    // Prepare the destination buffer and its size
    unsigned char *dstBuf = nullptr;
    size_t dstSize = 0;

    // Set transformation options
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform));
    transform.op = TJXOP_NONE; // No transformation
    transform.options = 0;     // No options

    // Call the function-under-test
    int result = tj3Transform(handle, data, size, 1, &dstBuf, &dstSize, &transform);

    // Clean up
    if (dstBuf) {
        tjFree(dstBuf);
    }
    tjDestroy(handle);

    return 0;
}