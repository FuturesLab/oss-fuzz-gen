#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;
    }

    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    const unsigned char *yuvPlanes[3];
    int strides[3];
    unsigned char *dstBuffer = NULL;
    int width, height, subsamp, colorspace;
    int flags = 0;

    // Set up YUV planes and strides
    yuvPlanes[0] = data;
    yuvPlanes[1] = data + 1;
    yuvPlanes[2] = data + 2;

    strides[0] = 1;
    strides[1] = 1;
    strides[2] = 1;

    // Set arbitrary non-zero values for width, height, subsamp, and colorspace
    width = 1;
    height = 1;
    subsamp = TJSAMP_420;
    colorspace = TJCS_YCbCr;

    // Allocate destination buffer
    int pixelFormat = TJPF_RGB;
    int dstSize = tjBufSize(width, height, subsamp);
    dstBuffer = (unsigned char *)malloc(dstSize);
    if (dstBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecodeYUVPlanes(handle, yuvPlanes, strides, subsamp, dstBuffer, width, 0, height, pixelFormat, flags);

    // Clean up
    free(dstBuffer);
    tjDestroy(handle);

    return 0;
}