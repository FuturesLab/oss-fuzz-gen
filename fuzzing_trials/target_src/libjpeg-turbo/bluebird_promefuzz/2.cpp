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
#include <cstddef>
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

static void fuzzTjCompress2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 6) {
        return;
    } // Not enough data

    int width = Data[0] % 256 + 1;
    int height = Data[1] % 256 + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;
    int jpegSubsamp = Data[3] % TJ_NUMSAMP;
    int jpegQual = Data[4] % 101;
    int flags = Data[5] % 2 ? TJFLAG_NOREALLOC : 0;

    const unsigned char *srcBuf = Data + 6;
    if (Size < 6 + (size_t)width * height * tjPixelSize[pixelFormat]) {
        return;
    }

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 10 of tjCompress2
    tjCompress2(handle, srcBuf, width, 0, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, Size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (jpegBuf) {
        tjFree(jpegBuf);
    }
}

static void fuzzTjCompressFromYUVPlanes(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 5) {
        return;
    } // Not enough data

    int width = Data[0] % 256 + 1;
    int height = Data[1] % 256 + 1;
    int subsamp = Data[2] % TJ_NUMSAMP;
    int jpegQual = Data[3] % 101;
    int flags = Data[4] % 2 ? TJFLAG_NOREALLOC : 0;

    int numPlanes = tjMCUHeight[subsamp] == 16 ? 3 : 1;
    std::vector<const unsigned char *> srcPlanes(3, nullptr);
    std::vector<int> strides(3, 0);

    size_t offset = 5;
    for (int i = 0; i < numPlanes; i++) {
        int pw = tjPlaneWidth(i, width, subsamp);
        int ph = tjPlaneHeight(i, height, subsamp);
        int planeSize = pw * ph;
        if (Size < offset + planeSize) {
                return;
        }
        srcPlanes[i] = Data + offset;
        strides[i] = pw;
        offset += planeSize;
    }

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    tjCompressFromYUVPlanes(handle, srcPlanes.data(), width, strides.data(), height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    if (jpegBuf) {
        tjFree(jpegBuf);
    }
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    tjhandle handle = createHandle();
    if (!handle) {
        return 0;
    }

    fuzzTjCompress2(handle, Data, Size);
    fuzzTjCompressFromYUVPlanes(handle, Data, Size);

    int errorCode = tjGetErrorCode(handle);
    errorCode = tj3GetErrorCode(handle);

    destroyHandle(handle);
    return 0;
}