// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3CompressFromYUVPlanes8 at turbojpeg.c:1259:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <turbojpeg.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there is at least some data

    // Initialize TurboJPEG handle for compression
    tjhandle handleCompress = tjInitCompress();
    if (!handleCompress) return 0;

    // Initialize TurboJPEG handle for decompression
    tjhandle handleDecompress = tjInitDecompress();
    if (!handleDecompress) {
        tjDestroy(handleCompress);
        return 0;
    }

    // Set up variables for tj3CompressFromYUVPlanes8
    unsigned char *srcPlanes[3] = {nullptr, nullptr, nullptr};
    int width = 128, height = 128; // Example dimensions
    int strides[3] = {width, width / 2, width / 2};
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Allocate memory for Y, U, V planes
    srcPlanes[0] = (unsigned char *)malloc(width * height);
    srcPlanes[1] = (unsigned char *)malloc(width * height / 4);
    srcPlanes[2] = (unsigned char *)malloc(width * height / 4);

    if (srcPlanes[0] && srcPlanes[1] && srcPlanes[2]) {
        // Copy data to planes if size allows
        size_t copySize = width * height + 2 * (width * height / 4);
        if (Size >= copySize) {
            memcpy(srcPlanes[0], Data, width * height);
            memcpy(srcPlanes[1], Data + width * height, width * height / 4);
            memcpy(srcPlanes[2], Data + width * height + width * height / 4, width * height / 4);
        }

        // Call tj3CompressFromYUVPlanes8
        tj3CompressFromYUVPlanes8(handleCompress, srcPlanes, width, strides, height, &jpegBuf, &jpegSize);

        // Free JPEG buffer if it was allocated
        if (jpegBuf) {
            tjFree(jpegBuf);
            jpegBuf = nullptr;
        }
    }

    // Set up variables for tj3DecodeYUV8
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3); // RGB buffer
    int pixelFormat = TJPF_RGB;
    int pitch = 0; // Default pitch

    if (dstBuf) {
        // Call tj3DecodeYUV8
        tj3DecodeYUV8(handleDecompress, Data, 1, dstBuf, width, pitch, height, pixelFormat);

        // Free destination buffer
        free(dstBuf);
    }

    // Clean up
    free(srcPlanes[0]);
    free(srcPlanes[1]);
    free(srcPlanes[2]);
    tjDestroy(handleCompress);
    tjDestroy(handleDecompress);

    return 0;
}