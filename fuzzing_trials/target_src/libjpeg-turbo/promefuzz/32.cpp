// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDecompress2 at turbojpeg.c:2059:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjTransform at turbojpeg.c:3044:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDecompressToYUV2 at turbojpeg.c:2404:15 in turbojpeg.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <setjmp.h>

static tjhandle createDecompressor() {
    return tjInitDecompress();
}

static tjhandle createCompressor() {
    return tjInitCompress();
}

static void destroyHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize a TurboJPEG decompressor handle
    tjhandle decompressor = createDecompressor();
    if (!decompressor) {
        return 0;
    }

    // Initialize a TurboJPEG compressor handle
    tjhandle compressor = createCompressor();
    if (!compressor) {
        destroyHandle(decompressor);
        return 0;
    }

    // Prepare buffers and variables for tjTransform
    unsigned char *dstBufs[1] = {nullptr};
    unsigned long dstSizes[1] = {0};
    tjtransform transforms[1] = {0};
    int n = 1;
    int flags = 0;

    // Fuzz tjTransform
    tjTransform(decompressor, Data, Size, n, dstBufs, dstSizes, transforms, flags);

    // Clean up buffers
    for (int i = 0; i < n; i++) {
        if (dstBufs[i]) {
            tjFree(dstBufs[i]);
        }
    }

    // Fuzz tj3GetErrorCode
    tj3GetErrorCode(decompressor);

    // Prepare variables for tjDecompressHeader2
    int width = 0, height = 0, jpegSubsamp = 0;

    // Fuzz tjDecompressHeader2
    tjDecompressHeader2(decompressor, const_cast<unsigned char *>(Data), Size, &width, &height, &jpegSubsamp);

    // Prepare variables for tjCompress
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *compressedBuf = nullptr;
    unsigned long compressedSize = 0;
    int pixelSize = 3;
    int jpegQual = 75;

    // Fuzz tjCompress
    if (srcBuf) {
        memset(srcBuf, 0, width * height * pixelSize);
        tjCompress(compressor, srcBuf, width, width * pixelSize, height, pixelSize, compressedBuf, &compressedSize, jpegSubsamp, jpegQual, flags);
        tjFree(compressedBuf);
        free(srcBuf);
    }

    // Prepare variables for tjDecompressToYUV2
    unsigned char *yuvBuf = (unsigned char *)malloc(width * height * 3 / 2);

    // Fuzz tjDecompressToYUV2
    if (yuvBuf) {
        tjDecompressToYUV2(decompressor, Data, Size, yuvBuf, width, 4, height, flags);
        free(yuvBuf);
    }

    // Prepare variables for tjDecompress2
    unsigned char *decompressedBuf = (unsigned char *)malloc(width * height * pixelSize);

    // Fuzz tjDecompress2
    if (decompressedBuf) {
        tjDecompress2(decompressor, Data, Size, decompressedBuf, width, width * pixelSize, height, TJPF_RGB, flags);
        free(decompressedBuf);
    }

    // Clean up handles
    destroyHandle(decompressor);
    destroyHandle(compressor);

    return 0;
}