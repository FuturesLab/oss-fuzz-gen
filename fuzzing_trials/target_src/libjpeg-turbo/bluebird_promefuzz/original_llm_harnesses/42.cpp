// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:643:15 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1508:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1394:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tj3DecodeYUVPlanes8 at turbojpeg.c:2511:15 in turbojpeg.h
// tjGetErrorCode at turbojpeg.c:652:15 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <turbojpeg.h>

static tjhandle createTurboJPEGInstance() {
    tjhandle handle = tjInitCompress();
    if (!handle) {
        fprintf(stderr, "Error initializing TurboJPEG: %s\n", tjGetErrorStr());
        return nullptr;
    }
    return handle;
}

static void destroyTurboJPEGInstance(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = createTurboJPEGInstance();
    if (!handle) return 0;

    // Fuzzing tj3GetErrorCode
    int errorCode = tj3GetErrorCode(handle);

    // Fuzzing tjDecodeYUVPlanes
    const unsigned char *srcPlanes[3] = {Data, Data, Data};
    int strides[3] = {0, 0, 0};
    unsigned char *dstBuf = static_cast<unsigned char*>(malloc(Size));
    if (dstBuf) {
        tjDecodeYUVPlanes(handle, srcPlanes, strides, 0, dstBuf, 1, 0, 1, 0, 0);
        free(dstBuf);
    }

    // Fuzzing tj3EncodeYUVPlanes8
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int encodeStrides[3] = {0, 0, 0};
    tj3EncodeYUVPlanes8(handle, Data, 1, 0, 1, 0, dstPlanes, encodeStrides);

    // Fuzzing tjCompressFromYUVPlanes
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    tjCompressFromYUVPlanes(handle, srcPlanes, 1, strides, 1, 0, &jpegBuf, &jpegSize, 75, 0);
    tjFree(jpegBuf);

    // Fuzzing tj3DecodeYUVPlanes8
    unsigned char *decodeDstBuf = static_cast<unsigned char*>(malloc(Size));
    if (decodeDstBuf) {
        tj3DecodeYUVPlanes8(handle, srcPlanes, strides, decodeDstBuf, 1, 0, 1, 0);
        free(decodeDstBuf);
    }

    // Fuzzing tjGetErrorCode
    int errorCode2 = tjGetErrorCode(handle);

    destroyTurboJPEGInstance(handle);
    return 0;
}