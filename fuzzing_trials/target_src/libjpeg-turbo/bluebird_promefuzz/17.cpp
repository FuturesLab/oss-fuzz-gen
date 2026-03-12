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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize TurboJPEG handle
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Prepare parameters
    int width = 100; // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB;
    int pitch = width * tjPixelSize[pixelFormat]; // Correctly calculate pitch
    int subsamp = TJSAMP_420;
    int flags = 0;
    int jpegQual = 75;

    // Calculate minimum buffer size
    size_t minBufSize = width * height * tjPixelSize[pixelFormat];
    if (Size < minBufSize) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate buffers based on calculated size
    unsigned char *srcBuf = (unsigned char *)malloc(minBufSize);
    unsigned char *dstBuf = (unsigned char *)malloc(minBufSize);
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    if (!srcBuf || !dstBuf) {
        tjDestroy(handle);
        free(srcBuf);
        free(dstBuf);
        return 0;
    }

    // Copy data to source buffer
    memcpy(srcBuf, Data, minBufSize);

    // Fuzz tjEncodeYUV2
    tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, flags);

    // Fuzz tjEncodeYUV
    tjEncodeYUV(handle, srcBuf, width, pitch, height, tjPixelSize[pixelFormat], dstBuf, subsamp, flags);

    // Fuzz tjCompress2
    tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, subsamp, jpegQual, flags);

    // Fuzz tjCompressFromYUV
    tjCompressFromYUV(handle, srcBuf, width, 4, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Fuzz tj3CompressFromYUV8
    size_t jpegBufSize = 0;
    tj3CompressFromYUV8(handle, srcBuf, width, 4, height, &jpegBuf, &jpegBufSize);

    // Fuzz tjEncodeYUV3
    tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, 4, subsamp, flags);

    // Cleanup
    tjDestroy(handle);
    free(srcBuf);
    free(dstBuf);
    if (jpegBuf) tjFree(jpegBuf);

    return 0;
}