extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Define dimensions and subsampling
    int width = 64;
    int height = 64;
    int subsamp = TJSAMP_420;

    // Allocate memory for YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3] = { width, width / 2, width / 2 };
    yuvPlanes[0] = (unsigned char *)malloc(width * height);
    yuvPlanes[1] = (unsigned char *)malloc(width * height / 4);
    yuvPlanes[2] = (unsigned char *)malloc(width * height / 4);

    // Allocate memory for output buffer
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);

    if (yuvPlanes[0] && yuvPlanes[1] && yuvPlanes[2] && dstBuf) {
        // Call the function-under-test
        tj3DecodeYUVPlanes8(handle, (const unsigned char **)yuvPlanes, strides, dstBuf, width, 0, height, subsamp);
    }

    // Free allocated memory
    free(yuvPlanes[0]);
    free(yuvPlanes[1]);
    free(yuvPlanes[2]);
    free(dstBuf);

    // Destroy handle
    tjDestroy(handle);

    return 0;
}