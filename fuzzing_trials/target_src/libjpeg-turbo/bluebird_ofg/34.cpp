extern "C" {
    #include "../src/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0;
    } // Ensure there is enough data for the test

    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    const unsigned char *yuvPlanes[3];
    int strides[3];
    unsigned char *dstBuf;
    int width, height, subsamp, flags;

    // Determine width and height based on input size
    width = 8; // Minimal width
    height = size / (3 * width); // Calculate height based on available data

    if (height < 8) { // Ensure minimal height
        tjDestroy(handle);
        return 0;
    }

    // Set up YUV planes
    yuvPlanes[0] = data;
    yuvPlanes[1] = data + width * height;
    yuvPlanes[2] = data + 2 * width * height;

    // Set up strides
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Set up other parameters
    subsamp = TJSAMP_420; // Common subsampling
    flags = 0; // No specific flags

    // Allocate buffer for the destination
    dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 9 of tjDecodeYUVPlanes
    tjDecodeYUVPlanes(handle, yuvPlanes, strides, subsamp, dstBuf, width, 0, height, TJPF_RGB, TJXOPT_PROGRESSIVE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}