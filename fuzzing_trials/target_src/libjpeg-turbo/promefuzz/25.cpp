// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjEncodeYUV3 at turbojpeg.c:1734:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3DecodeYUVPlanes8 at turbojpeg.c:2511:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tj3CompressFromYUVPlanes8 at turbojpeg.c:1259:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2678:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1688:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1394:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:971:18 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
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
#include <iostream>

static void fuzz_tj3CompressFromYUVPlanes8(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for YUV planes

    tjhandle handle = tjInitCompress();
    if (!handle) return;

    int width = 256, height = 256;
    const unsigned char *srcPlanes[3] = { Data, Data + width * height, Data + width * height * 2 };
    int strides[3] = { width, width / 2, width / 2 };
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    tj3CompressFromYUVPlanes8(handle, srcPlanes, width, strides, height, &jpegBuf, &jpegSize);

    if (jpegBuf) tjFree(jpegBuf);
    tjDestroy(handle);
}

static void fuzz_tj3DecodeYUV8(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for YUV buffer

    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    int width = 256, height = 256, align = 1, pixelFormat = TJPF_RGB;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }

    tj3DecodeYUV8(handle, Data, align, dstBuf, width, width * tjPixelSize[pixelFormat], height, pixelFormat);

    free(dstBuf);
    tjDestroy(handle);
}

static void fuzz_tj3EncodeYUV8(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for RGB buffer

    tjhandle handle = tjInitCompress();
    if (!handle) return;

    int width = 256, height = 256, pixelFormat = TJPF_RGB, align = 1;
    unsigned char *dstBuf = (unsigned char *)malloc(tj3YUVBufSize(width, height, align, TJSAMP_444));
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }

    tj3EncodeYUV8(handle, Data, width, width * tjPixelSize[pixelFormat], height, pixelFormat, dstBuf, align);

    free(dstBuf);
    tjDestroy(handle);
}

static void fuzz_tjCompressFromYUVPlanes(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for YUV planes

    tjhandle handle = tjInitCompress();
    if (!handle) return;

    int width = 256, height = 256, jpegQual = 75, flags = 0;
    const unsigned char *srcPlanes[3] = { Data, Data + width * height, Data + width * height * 2 };
    int strides[3] = { width, width / 2, width / 2 };
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, TJSAMP_444, &jpegBuf, &jpegSize, jpegQual, flags);

    if (jpegBuf) tjFree(jpegBuf);
    tjDestroy(handle);
}

static void fuzz_tjEncodeYUV3(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for RGB buffer

    tjhandle handle = tjInitCompress();
    if (!handle) return;

    int width = 256, height = 256, pixelFormat = TJPF_RGB, align = 1, subsamp = TJSAMP_444, flags = 0;
    unsigned char *dstBuf = (unsigned char *)malloc(tj3YUVBufSize(width, height, align, subsamp));
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }

    tjEncodeYUV3(handle, Data, width, width * tjPixelSize[pixelFormat], height, pixelFormat, dstBuf, align, subsamp, flags);

    free(dstBuf);
    tjDestroy(handle);
}

static void fuzz_tj3DecodeYUVPlanes8(const uint8_t *Data, size_t Size) {
    if (Size < 256 * 256 * 3) return; // Ensure enough data for YUV planes

    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    int width = 256, height = 256, pixelFormat = TJPF_RGB;
    const unsigned char *srcPlanes[3] = { Data, Data + width * height, Data + width * height * 2 };
    int strides[3] = { width, width / 2, width / 2 };
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }

    tj3DecodeYUVPlanes8(handle, srcPlanes, strides, dstBuf, width, width * tjPixelSize[pixelFormat], height, pixelFormat);

    free(dstBuf);
    tjDestroy(handle);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    fuzz_tj3CompressFromYUVPlanes8(Data, Size);
    fuzz_tj3DecodeYUV8(Data, Size);
    fuzz_tj3EncodeYUV8(Data, Size);
    fuzz_tjCompressFromYUVPlanes(Data, Size);
    fuzz_tjEncodeYUV3(Data, Size);
    fuzz_tj3DecodeYUVPlanes8(Data, Size);
    return 0;
}