#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, return early
    }

    // Assume we have 3 YUV planes for simplicity
    const int numPlanes = 3;
    const unsigned char *yuvPlanes[numPlanes];
    int strides[numPlanes];
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Initialize YUV planes and strides
    for (int i = 0; i < numPlanes; ++i) {
        yuvPlanes[i] = data;
        strides[i] = size / numPlanes;
    }

    // Set arbitrary width, height, and subsampling
    int width = 256;
    int height = 256;
    int subsampling = TJSAMP_420;

    // Call the function-under-test
    int result = tj3CompressFromYUVPlanes8(handle, yuvPlanes, width, strides, height, &jpegBuf, &jpegSize);

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}