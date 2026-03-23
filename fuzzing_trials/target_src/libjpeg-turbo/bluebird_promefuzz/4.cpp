#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../src/turbojpeg.h"

static tjhandle createDecompressor() {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        fprintf(stderr, "Failed to create TurboJPEG decompressor: %s\n", tjGetErrorStr());
        exit(1);
    }
    return handle;
}

static void destroyDecompressor(tjhandle handle) {
    if (tjDestroy(handle) != 0) {
        fprintf(stderr, "Failed to destroy TurboJPEG decompressor: %s\n", tjGetErrorStr());
    }
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0; // Ensure there's enough data to read basic parameters

    // Create a TurboJPEG decompressor handle
    tjhandle handle = createDecompressor();

    // Extract parameters from input data
    int align = 1 << (Data[0] % 4); // Alignment: 1, 2, 4, 8
    int width = (Data[1] % 256) + 1;
    int height = (Data[2] % 256) + 1;
    int pixelFormat = Data[3] % TJ_NUMPF;
    int subsamp = Data[4] % TJ_NUMSAMP;
    int pitch = width * tjPixelSize[pixelFormat];

    // Prepare buffers
    size_t yuvBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (Size < yuvBufSize + 10) {
        destroyDecompressor(handle);
        return 0;
    }

    const unsigned char *srcBuf = Data + 5;
    unsigned char *dstBuf = (unsigned char *)malloc(pitch * height);
    if (!dstBuf) {
        destroyDecompressor(handle);
        return 0;
    }

    // Call tj3DecodeYUV8
    if (tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height, pixelFormat) == -1) {
        fprintf(stderr, "tj3DecodeYUV8 error: %s\n", tj3GetErrorStr(handle));
    }

    // Prepare parameters for tjDecodeYUVPlanes
    int planeSizes[3] = {
        tj3YUVPlaneWidth(0, width, subsamp) * height,
        tj3YUVPlaneWidth(1, width, subsamp) * (height / 2),
        tj3YUVPlaneWidth(2, width, subsamp) * (height / 2)
    };

    if (Size < planeSizes[0] + planeSizes[1] + planeSizes[2] + 5) {
        free(dstBuf);
        destroyDecompressor(handle);
        return 0;
    }

    const unsigned char *srcPlanes[3] = {srcBuf, srcBuf + planeSizes[0], srcBuf + planeSizes[0] + planeSizes[1]};
    int strides[3] = {tj3YUVPlaneWidth(0, width, subsamp), tj3YUVPlaneWidth(1, width, subsamp), tj3YUVPlaneWidth(2, width, subsamp)};

    if (tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, pitch, height, pixelFormat, 0) == -1) {
        fprintf(stderr, "tjDecodeYUVPlanes error: %s\n", tj3GetErrorStr(handle));
    }

    // Prepare parameters for tjEncodeYUV
    if (tjEncodeYUV(handle, dstBuf, width, pitch, height, tjPixelSize[pixelFormat], dstBuf, subsamp, 0) == -1) {
        fprintf(stderr, "tjEncodeYUV error: %s\n", tj3GetErrorStr(handle));
    }

    // Prepare parameters for tjDecodeYUV
    if (tjDecodeYUV(handle, srcBuf, align, subsamp, dstBuf, width, pitch, height, pixelFormat, 0) == -1) {
        fprintf(stderr, "tjDecodeYUV error: %s\n", tj3GetErrorStr(handle));
    }

    // Prepare parameters for tjEncodeYUV2
    if (tjEncodeYUV2(handle, dstBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, 0) == -1) {
        fprintf(stderr, "tjEncodeYUV2 error: %s\n", tj3GetErrorStr(handle));
    }

    // Cleanup
    free(dstBuf);
    destroyDecompressor(handle);
    return 0;
}