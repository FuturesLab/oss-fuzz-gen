// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3Get at turbojpeg.c:807:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tj3DecodeYUVPlanes8 at turbojpeg.c:2511:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjInitTransform at turbojpeg.c:2751:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1508:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1688:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjInitTransform at turbojpeg.c:2751:20 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
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

static void fuzz_tj3DecodeYUV8(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = 1 << (Data[2] % 4); // 1, 2, 4, 8
    int pixelFormat = Data[3] % TJ_NUMPF;

    size_t yuvSize = tj3YUVBufSize(width, align, height, TJSAMP_444);
    if (Size < yuvSize + 8) return;

    const unsigned char *srcBuf = Data + 4;
    unsigned char *dstBuf = new unsigned char[width * height * tjPixelSize[pixelFormat]];

    int pitch = width * tjPixelSize[pixelFormat];
    int result = tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height, pixelFormat);
    if (result != 0) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tj3DecodeYUV8 error: " << errStr << std::endl;
    }

    delete[] dstBuf;
}

static void fuzz_tj3EncodeYUVPlanes8(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;

    size_t rgbSize = width * height * tjPixelSize[pixelFormat];
    if (Size < rgbSize + 8) return;

    const unsigned char *srcBuf = Data + 4;
    unsigned char *dstPlanes[3];
    int strides[3];

    for (int i = 0; i < 3; i++) {
        strides[i] = width;
        dstPlanes[i] = new unsigned char[width * height];
    }

    int result = tj3EncodeYUVPlanes8(handle, srcBuf, width, width * tjPixelSize[pixelFormat], height, pixelFormat, dstPlanes, strides);
    if (result != 0) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tj3EncodeYUVPlanes8 error: " << errStr << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        delete[] dstPlanes[i];
    }
}

static void fuzz_tj3EncodeYUV8(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = 1 << (Data[2] % 4); // 1, 2, 4, 8
    int pixelFormat = Data[3] % TJ_NUMPF;

    size_t rgbSize = width * height * tjPixelSize[pixelFormat];
    if (Size < rgbSize + 8) return;

    const unsigned char *srcBuf = Data + 4;
    size_t yuvSize = tj3YUVBufSize(width, align, height, TJSAMP_444);
    unsigned char *dstBuf = new unsigned char[yuvSize];

    int result = tj3EncodeYUV8(handle, srcBuf, width, width * tjPixelSize[pixelFormat], height, pixelFormat, dstBuf, align);
    if (result != 0) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tj3EncodeYUV8 error: " << errStr << std::endl;
    }

    delete[] dstBuf;
}

static void fuzz_tjInitTransform() {
    tjhandle handle = tjInitTransform();
    if (handle == nullptr) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tjInitTransform error: " << errStr << std::endl;
    } else {
        tjDestroy(handle);
    }
}

static void fuzz_tj3Get(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    int param = Data[0]; // Assuming a valid parameter range
    int value = tj3Get(handle, param);
    if (value == -1) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tj3Get error: " << errStr << std::endl;
    }
}

static void fuzz_tj3DecodeYUVPlanes8(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int pixelFormat = Data[2] % TJ_NUMPF;

    const unsigned char *srcPlanes[3];
    int strides[3];
    size_t planeSize = width * height;

    if (Size < planeSize * 3 + 8) return;

    srcPlanes[0] = Data + 4;
    srcPlanes[1] = Data + 4 + planeSize;
    srcPlanes[2] = Data + 4 + planeSize * 2;

    for (int i = 0; i < 3; i++) {
        strides[i] = width;
    }

    unsigned char *dstBuf = new unsigned char[width * height * tjPixelSize[pixelFormat]];

    int pitch = width * tjPixelSize[pixelFormat];
    int result = tj3DecodeYUVPlanes8(handle, srcPlanes, strides, dstBuf, width, pitch, height, pixelFormat);
    if (result != 0) {
        const char *errStr = tjGetErrorStr();
        std::cerr << "tj3DecodeYUVPlanes8 error: " << errStr << std::endl;
    }

    delete[] dstBuf;
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    tjhandle handle = tjInitTransform();
    if (handle == nullptr) return 0;

    fuzz_tj3DecodeYUV8(handle, Data, Size);
    fuzz_tj3EncodeYUVPlanes8(handle, Data, Size);
    fuzz_tj3EncodeYUV8(handle, Data, Size);
    fuzz_tj3Get(handle, Data, Size);
    fuzz_tj3DecodeYUVPlanes8(handle, Data, Size);

    tjDestroy(handle);
    fuzz_tjInitTransform();

    return 0;
}