// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1758:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1508:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1688:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    // Fuzzing tj3DecodeYUV8
    {
        int width = 64;
        int height = 64;
        int pixelFormat = TJPF_RGB;
        int align = 4;
        size_t yuvBufSize = tj3YUVBufSize(width, align, height, TJSAMP_420);
        if (Size >= yuvBufSize + width * height * 3) {
            const unsigned char *srcBuf = Data;
            unsigned char *dstBuf = new unsigned char[width * height * 3];
            int pitch = width * tjPixelSize[pixelFormat];
            tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height, pixelFormat);
            delete[] dstBuf;
        }
    }

    // Fuzzing tj3EncodeYUVPlanes8
    {
        int width = 64;
        int height = 64;
        int pixelFormat = TJPF_RGB;
        int pitch = width * tjPixelSize[pixelFormat];
        unsigned char *srcBuf = new unsigned char[pitch * height];
        unsigned char *dstPlanes[3];
        int strides[3] = {width, width / 2, width / 2};
        size_t planeSize = tj3YUVBufSize(width, 1, height, TJSAMP_420) / 3;
        for (int i = 0; i < 3; i++) {
            dstPlanes[i] = new unsigned char[planeSize];
        }
        if (Size >= pitch * height) {
            memcpy(srcBuf, Data, pitch * height);
            tj3EncodeYUVPlanes8(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, strides);
        }
        delete[] srcBuf;
        for (int i = 0; i < 3; i++) {
            delete[] dstPlanes[i];
        }
    }

    // Fuzzing tjDecodeYUVPlanes
    {
        int width = 64;
        int height = 64;
        int pixelFormat = TJPF_RGB;
        int subsamp = TJSAMP_420;
        int flags = 0;
        unsigned char *dstBuf = new unsigned char[width * height * tjPixelSize[pixelFormat]];
        const unsigned char *srcPlanes[3];
        int strides[3] = {width, width / 2, width / 2};
        size_t planeSize = tj3YUVBufSize(width, 1, height, subsamp) / 3;
        for (int i = 0; i < 3; i++) {
            if (Size >= (i + 1) * planeSize) {
                srcPlanes[i] = Data + i * planeSize;
            } else {
                srcPlanes[i] = nullptr;
            }
        }
        tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, width * tjPixelSize[pixelFormat], height, pixelFormat, flags);
        delete[] dstBuf;
    }

    // Fuzzing tj3EncodeYUV8
    {
        int width = 64;
        int height = 64;
        int pixelFormat = TJPF_RGB;
        int pitch = width * tjPixelSize[pixelFormat];
        int align = 4;
        size_t yuvBufSize = tj3YUVBufSize(width, align, height, TJSAMP_420);
        if (Size >= pitch * height + yuvBufSize) {
            const unsigned char *srcBuf = Data;
            unsigned char *dstBuf = new unsigned char[yuvBufSize];
            tj3EncodeYUV8(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, align);
            delete[] dstBuf;
        }
    }

    // Fuzzing tjEncodeYUV2
    {
        int width = 64;
        int height = 64;
        int pixelFormat = TJPF_RGB;
        int pitch = width * tjPixelSize[pixelFormat];
        int subsamp = TJSAMP_420;
        int flags = 0;
        size_t yuvBufSize = tj3YUVBufSize(width, 1, height, subsamp);
        if (Size >= pitch * height + yuvBufSize) {
            unsigned char *srcBuf = new unsigned char[pitch * height];
            unsigned char *dstBuf = new unsigned char[yuvBufSize];
            memcpy(srcBuf, Data, pitch * height);
            tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, flags);
            delete[] srcBuf;
            delete[] dstBuf;
        }
    }

    tjDestroy(handle);
    return 0;
}