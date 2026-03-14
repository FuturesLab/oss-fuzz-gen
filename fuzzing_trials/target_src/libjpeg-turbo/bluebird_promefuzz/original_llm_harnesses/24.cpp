// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:999:25 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1758:15 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tjEncodeYUV at turbojpeg.c:1767:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2724:15 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
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
#include <stdexcept>

static tjhandle getHandle() {
    tjhandle handle = tjInitCompress();
    if (!handle) {
        throw std::runtime_error("Failed to initialize TurboJPEG handle");
    }
    return handle;
}

static void cleanupHandle(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    const int width = 256;
    const int height = 256;
    const int pixelFormat = TJPF_RGB;
    const int bytesPerPixel = tjPixelSize[pixelFormat];
    const int requiredSize = width * height * bytesPerPixel;

    if (Size < requiredSize) return 0;

    tjhandle handle = nullptr;
    try {
        handle = getHandle();

        // Test tjEncodeYUV2
        unsigned char *srcBuf = const_cast<unsigned char*>(Data);
        int pitch = width * bytesPerPixel;
        int subsamp = TJSAMP_444;
        int flags = 0;
        unsigned char *dstBuf = new unsigned char[tjBufSizeYUV2(width, 4, height, subsamp)];

        tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, flags);

        // Test tjDecodeYUVPlanes
        const unsigned char *srcPlanes[3] = { Data, Data, Data };
        int strides[3] = { width, width / 2, width / 2 };
        unsigned char *dstBufDecode = new unsigned char[width * height * 3];

        tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBufDecode, width, pitch, height, pixelFormat, flags);

        // Test tjEncodeYUV
        tjEncodeYUV(handle, srcBuf, width, pitch, height, 4, dstBuf, subsamp, flags);

        // Test tj3YUVBufSize
        size_t yuvBufSize = tj3YUVBufSize(width, 4, height, subsamp);

        // Test tjDecodeYUV
        tjDecodeYUV(handle, Data, 4, subsamp, dstBufDecode, width, pitch, height, pixelFormat, flags);

        // Test tj3DecodeYUV8
        tj3DecodeYUV8(handle, Data, 4, dstBufDecode, width, pitch, height, pixelFormat);

        delete[] dstBuf;
        delete[] dstBufDecode;
    } catch (const std::exception &e) {
        // Handle any errors
    }

    cleanupHandle(handle);
    return 0;
}