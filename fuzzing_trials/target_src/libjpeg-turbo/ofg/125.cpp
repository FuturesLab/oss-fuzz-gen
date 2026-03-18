#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Define the number of planes
    const int numPlanes = 3;
    
    // Initialize YUV planes
    const unsigned char *yuvPlanes[numPlanes];
    int planeSizes[numPlanes];
    for (int i = 0; i < numPlanes; ++i) {
        yuvPlanes[i] = data;
        planeSizes[i] = size / numPlanes;
    }

    // Allocate memory for the destination buffer
    unsigned char *dstBuf = (unsigned char *)malloc(size);
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Set width, height, and pixel format
    int width = 64;  // example width
    int height = 64; // example height
    int pitch = width * 3; // assuming 3 bytes per pixel for RGB
    int pixelFormat = TJPF_RGB;

    // Call the function-under-test
    tj3DecodeYUVPlanes8(handle, yuvPlanes, planeSizes, dstBuf, width, pitch, height, pixelFormat);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}