// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjBufSizeYUV at turbojpeg.c:1007:25 in turbojpeg.h
// tjDecompressToYUV2 at turbojpeg.c:2404:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tjBufSize at turbojpeg.c:933:25 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2059:15 in turbojpeg.h
// tjTransform at turbojpeg.c:3044:15 in turbojpeg.h
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

static tjhandle createHandle() {
    return tjInitCompress();
}

static void destroyHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

static void fuzz_tj3GetErrorCode(tjhandle handle) {
    int errorCode = tj3GetErrorCode(handle);
    (void)errorCode; // Suppress unused variable warning
}

static void fuzz_tjCompress(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimal data for width, height, etc.

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelSize = Data[2] % 4 + 1;
    int jpegQual = Data[3] % 100 + 1;
    int jpegSubsamp = Data[4] % 5;
    int flags = Data[5] % 2;

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSize(width, height, jpegSubsamp));
    unsigned long compressedSize = 0;

    if (srcBuf && dstBuf) {
        memcpy(srcBuf, Data + 6, std::min(Size - 6, (size_t)(width * height * pixelSize)));
        tjCompress(handle, srcBuf, width, 0, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);
    }

    free(srcBuf);
    free(dstBuf);
}

static void fuzz_tjDecompressHeader2(tjhandle handle, const uint8_t *Data, size_t Size) {
    int width = 0, height = 0, jpegSubsamp = 0;
    tjDecompressHeader2(handle, (unsigned char *)Data, Size, &width, &height, &jpegSubsamp);
}

static void fuzz_tjDecompress2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimal data for width, height, etc.

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % 5;
    int flags = Data[3] % 2;

    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);

    if (dstBuf) {
        tjDecompress2(handle, Data, Size, dstBuf, width, 0, height, pixelFormat, flags);
        free(dstBuf);
    }
}

static void fuzz_tjTransform(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimal data for transformations

    int n = Data[0] % 5 + 1;
    int flags = Data[1] % 2;

    unsigned char **dstBufs = (unsigned char **)malloc(n * sizeof(unsigned char *));
    unsigned long *dstSizes = (unsigned long *)malloc(n * sizeof(unsigned long));
    tjtransform *transforms = (tjtransform *)malloc(n * sizeof(tjtransform));

    if (dstBufs && dstSizes && transforms) {
        for (int i = 0; i < n; i++) {
            dstBufs[i] = nullptr;
            dstSizes[i] = 0;
            transforms[i].op = Data[2 + i] % 8;
            transforms[i].data = nullptr;
            transforms[i].customFilter = nullptr;
        }
        tjTransform(handle, Data, Size, n, dstBufs, dstSizes, transforms, flags);

        for (int i = 0; i < n; i++) {
            free(dstBufs[i]);
        }
    }

    free(dstBufs);
    free(dstSizes);
    free(transforms);
}

static void fuzz_tjDecompressToYUV2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) return; // Ensure minimal data for width, height, etc.

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = Data[2] % 4 + 1;
    int flags = Data[3] % 2;

    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV(width, height, TJ_420));

    if (dstBuf) {
        tjDecompressToYUV2(handle, Data, Size, dstBuf, width, align, height, flags);
        free(dstBuf);
    }
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    tjhandle handle = createHandle();
    if (!handle) return 0;

    fuzz_tj3GetErrorCode(handle);
    fuzz_tjCompress(handle, Data, Size);
    fuzz_tjDecompressHeader2(handle, Data, Size);
    fuzz_tjDecompress2(handle, Data, Size);
    fuzz_tjTransform(handle, Data, Size);
    fuzz_tjDecompressToYUV2(handle, Data, Size);

    destroyHandle(handle);
    return 0;
}