#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there is at least some data

    tjhandle handle = tjInitTransform();
    if (!handle) return 0; // If initialization fails, return

    // Allocate memory for the destination buffer
    unsigned long destSize = size * 2; // Arbitrary size, adjust as needed
    unsigned char *destBuffer = (unsigned char *)malloc(destSize);
    if (!destBuffer) {
        tjDestroy(handle);
        return 0; // If memory allocation fails, return
    }

    // Initialize transformation parameters
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform));
    transform.op = TJXOP_NONE; // No transformation
    transform.options = 0;

    // Call the function-under-test
    int result = tjTransform(handle, data, size, 1, &destBuffer, &destSize, &transform, 0);

    // Clean up
    free(destBuffer);
    tjDestroy(handle);

    return 0;
}