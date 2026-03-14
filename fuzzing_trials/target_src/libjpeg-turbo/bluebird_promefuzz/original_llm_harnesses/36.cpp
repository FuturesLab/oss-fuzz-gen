// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3SetICCProfile at turbojpeg.c:1164:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1164:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Transform at turbojpeg.c:2870:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
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
#include <cstdlib>
#include <cstring>
#include <iostream>

static void fuzz_tj3SetICCProfile(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        unsigned char *iccBuf = (unsigned char *)malloc(Size);
        if (!iccBuf) return;
        memcpy(iccBuf, Data, Size);
        int ret = tj3SetICCProfile(handle, iccBuf, Size);
        if (ret == -1) {
            std::cerr << "Error in tj3SetICCProfile: " << tj3GetErrorStr(handle) << std::endl;
        }
        free(iccBuf);
    } else {
        int ret = tj3SetICCProfile(handle, nullptr, 0);
        if (ret == -1) {
            std::cerr << "Error in tj3SetICCProfile: " << tj3GetErrorStr(handle) << std::endl;
        }
    }
}

static void fuzz_tj3Transform(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tjtransform)) return;

    unsigned char *jpegBuf = (unsigned char *)malloc(Size);
    if (!jpegBuf) return;
    memcpy(jpegBuf, Data, Size);

    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform));

    unsigned char *dstBufs[1] = {nullptr};
    size_t dstSizes[1] = {0};

    int ret = tj3Transform(handle, jpegBuf, Size, 1, dstBufs, dstSizes, &transform);
    if (ret == -1) {
        std::cerr << "Error in tj3Transform: " << tj3GetErrorStr(handle) << std::endl;
    }

    if (dstBufs[0]) free(dstBufs[0]);
    free(jpegBuf);
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        std::cerr << "Error initializing TurboJPEG: " << tj3GetErrorStr(nullptr) << std::endl;
        return 0;
    }

    fuzz_tj3SetICCProfile(handle, Data, Size);
    fuzz_tj3Transform(handle, Data, Size);

    tj3Destroy(handle);
    return 0;
}