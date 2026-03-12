#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize variables for tjDecodeYUVPlanes
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the data size is sufficient for the parameters
    if (size < 6) {
        tjDestroy(handle);
        return 0;
    }

    // Set up the YUV planes
    const unsigned char *yuvPlanes[3];
    const int planeSizes[3] = {1, 1, 1}; // Minimal size for each plane
    yuvPlanes[0] = data;
    yuvPlanes[1] = data + 1;
    yuvPlanes[2] = data + 2;

    // Image dimensions and subsampling
    int width = 1;
    int height = 1;
    int subsamp = TJSAMP_444; // Use a valid subsampling option
    int flags = 0;

    // Output buffer
    unsigned char *dstBuf = new unsigned char[width * height * tjPixelSize[TJPF_RGB]];

    // Call the function under test
    tjDecodeYUVPlanes(handle, yuvPlanes, planeSizes, width, dstBuf, width, height, TJPF_RGB, subsamp, flags);

    // Clean up
    delete[] dstBuf;
    tjDestroy(handle);

    return 0;
}