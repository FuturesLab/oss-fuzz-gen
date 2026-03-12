#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there's enough data to work with
    }

    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0; // Failed to initialize compressor
    }

    // Set up YUV planes
    const unsigned char *yuvPlanes[3];
    int yuvStrides[3];
    int width = 2; // Minimal width for YUV
    int height = 2; // Minimal height for YUV

    // Allocate memory for YUV planes
    unsigned char *yPlane = new unsigned char[width * height];
    unsigned char *uPlane = new unsigned char[width * height / 4];
    unsigned char *vPlane = new unsigned char[width * height / 4];

    // Fill the YUV planes with data
    memcpy(yPlane, data, width * height);
    memcpy(uPlane, data + width * height, width * height / 4);
    memcpy(vPlane, data + width * height + width * height / 4, width * height / 4);

    yuvPlanes[0] = yPlane;
    yuvPlanes[1] = uPlane;
    yuvPlanes[2] = vPlane;

    yuvStrides[0] = width;
    yuvStrides[1] = width / 2;
    yuvStrides[2] = width / 2;

    // Set up output buffer
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Compress from YUV planes
    int subsample = TJSAMP_420; // Common subsampling
    int flags = 0; // No flags

    tjCompressFromYUVPlanes(handle, yuvPlanes, width, yuvStrides, height, subsample, &jpegBuf, &jpegSize, 100, flags);

    // Clean up
    tjDestroy(handle);
    tjFree(jpegBuf);
    delete[] yPlane;
    delete[] uPlane;
    delete[] vPlane;

    return 0;
}