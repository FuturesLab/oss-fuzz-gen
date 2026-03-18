// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3SetICCProfile at turbojpeg.c:1164:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Transform at turbojpeg.c:2870:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tj3TransformBufSize at turbojpeg.c:2831:18 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void fuzz_tj3SetICCProfile(tjhandle handle, const uint8_t *Data, size_t Size) {
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;

    if (Size > 0) {
        iccBuf = const_cast<unsigned char *>(Data);
        iccSize = Size;
    }

    if (tj3SetICCProfile(handle, iccBuf, iccSize) == -1) {
        tj3GetErrorStr(handle);
    }
}

static void fuzz_tj3Transform(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    unsigned char *jpegBuf = const_cast<unsigned char *>(Data);
    size_t jpegSize = Size;
    int n = 1;

    unsigned char *dstBufs[1] = {nullptr};
    size_t dstSizes[1] = {0};

    tjtransform transforms[1] = {};
    transforms[0].op = TJXOP_NONE;

    if (tj3Transform(handle, jpegBuf, jpegSize, n, dstBufs, dstSizes, transforms) == -1) {
        tj3GetErrorStr(handle);
    }

    if (dstBufs[0]) {
        tj3Free(dstBufs[0]);
    }
}

static void fuzz_tj3TransformBufSize(tjhandle handle) {
    tjtransform transform = {};
    size_t bufSize = tj3TransformBufSize(handle, &transform);
    (void)bufSize; // Avoid unused variable warning
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_TRANSFORM);
    if (!handle) {
        return 0;
    }

    fuzz_tj3SetICCProfile(handle, Data, Size);
    fuzz_tj3Transform(handle, Data, Size);
    fuzz_tj3TransformBufSize(handle);

    tj3Destroy(handle);
    return 0;
}