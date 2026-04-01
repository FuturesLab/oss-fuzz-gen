// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tj3DecompressToYUVPlanes8 at turbojpeg.c:2125:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1476:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjDecompressToYUV at turbojpeg.c:2452:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjDecompress at turbojpeg.c:2111:15 in turbojpeg.h
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

static void writeDummyFile(const uint8_t* data, size_t size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

static void fuzz_tjCompressFromYUV(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitCompress();
    if (!handle) return;

    unsigned char* jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    int width = 128;
    int height = 128;
    int subsamp = TJSAMP_420;
    int jpegQual = 75;
    int flags = 0;
    int align = 4;

    if (Size >= width * height * 3 / 2) {
        int result = tjCompressFromYUV(handle, Data, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);
        if (result == 0) tjFree(jpegBuf);
    }

    tjDestroy(handle);
}

static void fuzz_tjDecompressToYUV(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    unsigned char* dstBuf = (unsigned char*)malloc(Size * 2);
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }
    int flags = 0;

    int result = tjDecompressToYUV(handle, const_cast<unsigned char*>(Data), Size, dstBuf, flags);
    free(dstBuf);

    tjDestroy(handle);
}

static void fuzz_tjDecompressToYUVPlanes(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    unsigned char* dstPlanes[3] = { nullptr, nullptr, nullptr };
    int width = 128;
    int height = 128;
    int strides[3] = { width, width / 2, width / 2 };
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = (unsigned char*)malloc(width * height / (i == 0 ? 1 : 4));
    }
    int flags = 0;

    int result = tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, flags);
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }

    tjDestroy(handle);
}

static void fuzz_tjDecompress(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    unsigned char* dstBuf = (unsigned char*)malloc(Size * 2);
    if (!dstBuf) {
        tjDestroy(handle);
        return;
    }
    int width = 128;
    int height = 128;
    int pixelSize = 3;
    int flags = 0;
    int pitch = width * pixelSize;

    int result = tjDecompress(handle, const_cast<unsigned char*>(Data), Size, dstBuf, width, pitch, height, pixelSize, flags);
    free(dstBuf);

    tjDestroy(handle);
}

static void fuzz_tjCompress(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitCompress();
    if (!handle) return;

    unsigned char* dstBuf = nullptr;
    unsigned long compressedSize = 0;
    int width = 128;
    int height = 128;
    int pixelSize = 3;
    int jpegSubsamp = TJSAMP_420;
    int jpegQual = 75;
    int flags = 0;
    int pitch = width * pixelSize;

    if (Size >= width * height * pixelSize) {
        dstBuf = (unsigned char*)malloc(Size);
        if (dstBuf) {
            int result = tjCompress(handle, const_cast<unsigned char*>(Data), width, pitch, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);
            if (result == 0) tjFree(dstBuf);
        }
    }

    tjDestroy(handle);
}

static void fuzz_tj3DecompressToYUVPlanes8(const uint8_t* Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) return;

    unsigned char* dstPlanes[3] = { nullptr, nullptr, nullptr };
    int width = 128;
    int height = 128;
    int strides[3] = { width, width / 2, width / 2 };
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = (unsigned char*)malloc(width * height / (i == 0 ? 1 : 4));
    }

    int result = tj3DecompressToYUVPlanes8(handle, Data, Size, dstPlanes, strides);
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }

    tjDestroy(handle);
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t* Data, size_t Size) {
    writeDummyFile(Data, Size);

    fuzz_tjCompressFromYUV(Data, Size);
    fuzz_tjDecompressToYUV(Data, Size);
    fuzz_tjDecompressToYUVPlanes(Data, Size);
    fuzz_tjDecompress(Data, Size);
    fuzz_tjCompress(Data, Size);
    fuzz_tj3DecompressToYUVPlanes8(Data, Size);

    return 0;
}