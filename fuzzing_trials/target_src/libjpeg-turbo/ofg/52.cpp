#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitTransform();
    if (handle == nullptr) return 0;

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    int n = 1; // Number of transforms
    tjtransform transform;

    // Initialize transform structure
    memset(&transform, 0, sizeof(tjtransform));

    // Call the function-under-test
    int result = tj3Transform(handle, data, size, n, &jpegBuf, &jpegSize, &transform);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}