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
#include <cstdio>

static tjhandle createHandle() {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitCompress with tjInitTransform
    return tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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
    if (Size < 10) {
        return;
    } // Ensure minimal data for width, height, etc.

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

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 8 of tjCompress
        tjCompress(handle, srcBuf, width, 0, height, pixelSize, dstBuf, &compressedSize, TJXOPT_ARITHMETIC, jpegQual, flags);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }

    free(srcBuf);
    free(dstBuf);
}

static void fuzz_tjDecompressHeader2(tjhandle handle, const uint8_t *Data, size_t Size) {
    int width = 0, height = 0, jpegSubsamp = 0;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of tjDecompressHeader2
    int txjiufcn = 1;
    tjDecompressHeader2(handle, (unsigned char *)Data, Size, &txjiufcn, &height, &jpegSubsamp);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static void fuzz_tjDecompress2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) {
        return;
    } // Ensure minimal data for width, height, etc.

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
    if (Size < 10) {
        return;
    } // Ensure minimal data for transformations

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

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjTransform

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjTransform

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjTransform
        tjTransform(handle, Data, Size, n, dstBufs, dstSizes, transforms, TJ_NUMERR);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_ARG_MUTATOR



        for (int i = 0; i < n; i++) {
            free(dstBufs[i]);
        }
    }

    free(dstBufs);
    free(dstSizes);
    free(transforms);
}

static void fuzz_tjDecompressToYUV2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 10) {
        return;
    } // Ensure minimal data for width, height, etc.

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = Data[2] % 4 + 1;
    int flags = Data[3] % 2;

    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV(width, height, TJ_420));

    if (dstBuf) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjDecompressToYUV2

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 6 of tjDecompressToYUV2
        tjDecompressToYUV2(handle, Data, Size, dstBuf, width, align, TJ_BGR, TJFLAG_FORCEMMX);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_ARG_MUTATOR


        free(dstBuf);
    }
}

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    tjhandle handle = createHandle();
    if (!handle) {
        return 0;
    }

    fuzz_tj3GetErrorCode(handle);
    fuzz_tjCompress(handle, Data, Size);
    fuzz_tjDecompressHeader2(handle, Data, Size);
    fuzz_tjDecompress2(handle, Data, Size);
    fuzz_tjTransform(handle, Data, Size);
    fuzz_tjDecompressToYUV2(handle, Data, Size);

    destroyHandle(handle);
    return 0;
}