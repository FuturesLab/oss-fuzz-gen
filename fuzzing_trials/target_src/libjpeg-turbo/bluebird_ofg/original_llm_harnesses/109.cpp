#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    unsigned char *yuvPlanes[3] = { nullptr, nullptr, nullptr };
    int strides[3] = { 0, 0, 0 };

    // Assume some reasonable width and height for the YUV image
    int width = 640;
    int height = 480;
    int subsamp = TJSAMP_420; // Common subsampling format

    // Allocate memory for YUV planes
    yuvPlanes[0] = new unsigned char[width * height];
    yuvPlanes[1] = new unsigned char[width * height / 4];
    yuvPlanes[2] = new unsigned char[width * height / 4];

    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Call the function-under-test
    tj3DecompressToYUVPlanes8(handle, data, size, yuvPlanes, strides);

    // Clean up
    delete[] yuvPlanes[0];
    delete[] yuvPlanes[1];
    delete[] yuvPlanes[2];
    tjDestroy(handle);

    return 0;
}