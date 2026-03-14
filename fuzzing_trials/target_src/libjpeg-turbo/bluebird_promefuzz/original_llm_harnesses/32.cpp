// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2724:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:999:25 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1758:15 in turbojpeg.h
// tjPlaneSizeYUV at turbojpeg.c:1048:25 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:999:25 in turbojpeg.h
// tjEncodeYUV at turbojpeg.c:1767:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
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

static void fuzz_tjEncodeYUV2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;
    int subsamp = Data[3] % TJ_NUMSAMP;

    size_t srcBufSize = width * height * tjPixelSize[pixelFormat];
    if (Size < 4 + srcBufSize) return;

    unsigned char *srcBuf = (unsigned char *)(Data + 4);
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, subsamp));

    if (dstBuf) {
        tjEncodeYUV2(handle, srcBuf, width, 0, height, pixelFormat, dstBuf, subsamp, 0);
        free(dstBuf);
    }
}

static void fuzz_tjDecodeYUVPlanes(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 6) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;
    int subsamp = Data[3] % TJ_NUMSAMP;
    int numPlanes = 3; // Y, U, V planes
    int stride = Data[4] + 1;

    const unsigned char *srcPlanes[3];
    const int strides[3] = {stride, stride / 2, stride / 2};
    size_t planeSizes[3];

    for (int i = 0; i < numPlanes; i++) {
        planeSizes[i] = tjPlaneSizeYUV(i, width, strides[i], height, subsamp);
        if (Size < 6 + planeSizes[i]) return;
        srcPlanes[i] = Data + 6 + (i > 0 ? planeSizes[i - 1] : 0);
    }

    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuf) {
        tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, 0, height, pixelFormat, 0);
        free(dstBuf);
    }
}

static void fuzz_tjEncodeYUV(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelSize = Data[2] % 4 + 1;
    int subsamp = Data[3] % TJ_NUMSAMP;

    size_t srcBufSize = width * height * pixelSize;
    if (Size < 4 + srcBufSize) return;

    unsigned char *srcBuf = (unsigned char *)(Data + 4);
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, subsamp));

    if (dstBuf) {
        tjEncodeYUV(handle, srcBuf, width, 0, height, pixelSize, dstBuf, subsamp, 0);
        free(dstBuf);
    }
}

static void fuzz_tj3YUVBufSize(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    int width = Data[0] + 1;
    int align = 1 << (Data[1] % 3);
    int height = Data[2] + 1;
    int subsamp = Data[3] % TJ_NUMSAMP;

    tj3YUVBufSize(width, align, height, subsamp);
}

static void fuzz_tjDecodeYUV(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 5) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;
    int subsamp = Data[3] % TJ_NUMSAMP;
    int align = 1 << (Data[4] % 3);

    size_t srcBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (Size < 5 + srcBufSize) return;

    const unsigned char *srcBuf = Data + 5;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);

    if (dstBuf) {
        tjDecodeYUV(handle, srcBuf, align, subsamp, dstBuf, width, 0, height, pixelFormat, 0);
        free(dstBuf);
    }
}

static void fuzz_tj3DecodeYUV8(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 5) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;
    int align = 1 << (Data[3] % 3);
    int pitch = Data[4] + 1;

    size_t srcBufSize = tj3YUVBufSize(width, align, height, TJ_NUMSAMP);
    if (Size < 5 + srcBufSize) return;

    const unsigned char *srcBuf = Data + 5;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);

    if (dstBuf) {
        tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height, pixelFormat);
        free(dstBuf);
    }
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    fuzz_tjEncodeYUV2(handle, Data, Size);
    fuzz_tjDecodeYUVPlanes(handle, Data, Size);
    fuzz_tjEncodeYUV(handle, Data, Size);
    fuzz_tj3YUVBufSize(Data, Size);
    fuzz_tjDecodeYUV(handle, Data, Size);
    fuzz_tj3DecodeYUV8(handle, Data, Size);

    tjDestroy(handle);
    return 0;
}