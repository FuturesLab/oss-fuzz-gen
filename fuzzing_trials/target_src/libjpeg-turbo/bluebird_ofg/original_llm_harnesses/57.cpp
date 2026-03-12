#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG handle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Set up the YUV planes
    const unsigned char *yuvPlanes[3];
    int strides[3];
    int width = 64;  // Example width
    int height = 64; // Example height

    // Allocate memory for YUV planes
    unsigned char *yPlane = new unsigned char[width * height];
    unsigned char *uPlane = new unsigned char[width * height / 4];
    unsigned char *vPlane = new unsigned char[width * height / 4];

    // Initialize YUV planes with non-null data
    for (int i = 0; i < width * height; i++) {
        yPlane[i] = data[i % size];
    }
    for (int i = 0; i < width * height / 4; i++) {
        uPlane[i] = data[i % size];
        vPlane[i] = data[i % size];
    }

    yuvPlanes[0] = yPlane;
    yuvPlanes[1] = uPlane;
    yuvPlanes[2] = vPlane;

    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Output buffer
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3CompressFromYUVPlanes8(handle, yuvPlanes, width, strides, height, &jpegBuf, &jpegSize);

    // Clean up
    delete[] yPlane;
    delete[] uPlane;
    delete[] vPlane;
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tj3Destroy(handle);

    return 0;
}