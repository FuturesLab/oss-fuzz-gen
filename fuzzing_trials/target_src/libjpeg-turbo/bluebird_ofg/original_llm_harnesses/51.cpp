#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    unsigned long jpegSize = (unsigned long)size;
    unsigned char *jpegBuf = (unsigned char *)data;

    // Assume a maximum width and height for the image
    int width = 128;
    int height = 128;
    int subsamp, colorspace;

    // Allocate memory for the YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3];
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    yuvPlanes[0] = (unsigned char *)malloc(width * height);
    yuvPlanes[1] = (unsigned char *)malloc(width * height / 4);
    yuvPlanes[2] = (unsigned char *)malloc(width * height / 4);

    if (yuvPlanes[0] == NULL || yuvPlanes[1] == NULL || yuvPlanes[2] == NULL) {
        tjDestroy(handle);
        free(yuvPlanes[0]);
        free(yuvPlanes[1]);
        free(yuvPlanes[2]);
        return 0;
    }

    // Fuzz the function
    tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, yuvPlanes, width, strides, height, 0);

    // Clean up
    tjDestroy(handle);
    free(yuvPlanes[0]);
    free(yuvPlanes[1]);
    free(yuvPlanes[2]);

    return 0;
}