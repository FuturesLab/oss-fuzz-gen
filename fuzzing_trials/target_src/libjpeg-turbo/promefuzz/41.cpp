// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:999:25 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1758:15 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1204:15 in turbojpeg.h
// tjEncodeYUV at turbojpeg.c:1767:15 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1476:15 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1429:15 in turbojpeg.h
// tjEncodeYUV3 at turbojpeg.c:1734:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
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
#include <iostream>

static tjhandle initializeHandle() {
    tjhandle handle = tjInitCompress();
    if (!handle) {
        std::cerr << "Failed to initialize TurboJPEG handle: " << tjGetErrorStr() << std::endl;
    }
    return handle;
}

static void cleanupHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // Minimal size check for width, height, etc.

    int width = Data[0] | (Data[1] << 8);
    int height = Data[2] | (Data[3] << 8);
    int pixelFormat = Data[4] % TJ_NUMPF;
    int subsamp = Data[5] % TJ_NUMSAMP;
    int flags = Data[6];
    int jpegQual = Data[7] % 100;

    tjhandle handle = initializeHandle();
    if (!handle) return 0;

    size_t srcBufSize = width * height * tjPixelSize[pixelFormat];
    unsigned char *srcBuf = (unsigned char *)malloc(srcBufSize);
    if (!srcBuf) {
        cleanupHandle(handle);
        return 0;
    }
    memcpy(srcBuf, Data + 8, std::min(srcBufSize, Size - 8));

    int align = 4; // Assuming an alignment value
    size_t dstBufSize = tjBufSizeYUV2(width, align, height, subsamp);
    unsigned char *dstBuf = (unsigned char *)malloc(dstBufSize);
    if (!dstBuf) {
        free(srcBuf);
        cleanupHandle(handle);
        return 0;
    }

    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = nullptr;

    tjEncodeYUV2(handle, srcBuf, width, 0, height, pixelFormat, dstBuf, subsamp, flags);
    tjCompress2(handle, srcBuf, width, 0, height, pixelFormat, &jpegBuf, &jpegSize, subsamp, jpegQual, flags);
    tjEncodeYUV(handle, srcBuf, width, 0, height, tjPixelSize[pixelFormat], dstBuf, subsamp, flags);
    tjCompressFromYUV(handle, dstBuf, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);
    tj3CompressFromYUV8(handle, dstBuf, width, align, height, &jpegBuf, &jpegSize);
    tjEncodeYUV3(handle, srcBuf, width, 0, height, pixelFormat, dstBuf, align, subsamp, flags);

    free(srcBuf);
    free(dstBuf);
    if (jpegBuf) tjFree(jpegBuf);
    cleanupHandle(handle);

    return 0;
}