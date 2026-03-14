// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1164:15 in turbojpeg.h
// tj3Transform at turbojpeg.c:2870:15 in turbojpeg.h
// tj3TransformBufSize at turbojpeg.c:2831:18 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
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
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void handleError(tjhandle handle) {
    const char *errStr = tj3GetErrorStr(handle);
    if (errStr) {
        fprintf(stderr, "Error: %s\n", errStr);
    }
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        handleError(NULL);
        return 0;
    }

    // Fuzz tj3SetICCProfile
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;
    if (Size > 2) {
        iccBuf = const_cast<unsigned char*>(Data);
        iccSize = Size;
    }
    if (tj3SetICCProfile(handle, iccBuf, iccSize) != 0) {
        handleError(handle);
    }

    // Fuzz tj3Transform
    const unsigned char *jpegBuf = Data;
    size_t jpegSize = Size;
    int n = 1;
    unsigned char *dstBufs[1] = {nullptr};
    size_t dstSizes[1] = {0};
    tjtransform transforms[1] = {0};

    if (tj3Transform(handle, jpegBuf, jpegSize, n, dstBufs, dstSizes, transforms) != 0) {
        handleError(handle);
    }

    // Fuzz tj3TransformBufSize
    size_t maxBufSize = tj3TransformBufSize(handle, &transforms[0]);
    if (maxBufSize == 0) {
        handleError(handle);
    }

    // Cleanup
    for (int i = 0; i < n; i++) {
        if (dstBufs[i]) {
            tj3Free(dstBufs[i]);
        }
    }
    tj3Destroy(handle);

    return 0;
}