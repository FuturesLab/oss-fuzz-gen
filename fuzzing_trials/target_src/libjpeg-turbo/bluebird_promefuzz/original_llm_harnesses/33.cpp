// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjAlloc at turbojpeg.c:883:26 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2059:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tj3SaveImage16 at turbojpeg-mp.c:487:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjSaveImage at turbojpeg.c:3128:15 in turbojpeg.h
// tjLoadImage at turbojpeg.c:3107:26 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
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
#include <cstdio>
#include <cstring>

static void fuzz_tjAlloc(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(int)) {
        int bytes = *reinterpret_cast<const int*>(Data);
        unsigned char *buffer = tjAlloc(bytes);
        if (buffer) {
            tjFree(buffer);
        }
    }
}

static void fuzz_tjCompress(const uint8_t *Data, size_t Size) {
    if (Size >= 3 * sizeof(int) + sizeof(unsigned long)) {
        tjhandle handle = tjInitCompress();
        if (handle) {
            unsigned char *srcBuf = const_cast<unsigned char*>(Data);
            int width = *reinterpret_cast<const int*>(Data);
            int height = *reinterpret_cast<const int*>(Data + sizeof(int));
            int pixelSize = *reinterpret_cast<const int*>(Data + 2 * sizeof(int));
            unsigned long compressedSize = *reinterpret_cast<const unsigned long*>(Data + 3 * sizeof(int));
            unsigned char *dstBuf = static_cast<unsigned char*>(malloc(compressedSize));
            if (dstBuf) {
                tjCompress(handle, srcBuf, width, 0, height, pixelSize, dstBuf, &compressedSize, TJSAMP_444, 75, TJFLAG_FASTDCT);
                free(dstBuf);
            }
            tjDestroy(handle);
        }
    }
}

static void fuzz_tjDecompress2(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(unsigned long) + 4 * sizeof(int)) {
        tjhandle handle = tjInitDecompress();
        if (handle) {
            const unsigned char *jpegBuf = Data;
            unsigned long jpegSize = *reinterpret_cast<const unsigned long*>(Data);
            int width = *reinterpret_cast<const int*>(Data + sizeof(unsigned long));
            int height = *reinterpret_cast<const int*>(Data + sizeof(unsigned long) + sizeof(int));
            int pixelFormat = *reinterpret_cast<const int*>(Data + sizeof(unsigned long) + 2 * sizeof(int));
            unsigned char *dstBuf = static_cast<unsigned char*>(malloc(width * height * tjPixelSize[pixelFormat]));
            if (dstBuf) {
                tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, 0, height, pixelFormat, TJFLAG_FASTDCT);
                free(dstBuf);
            }
            tjDestroy(handle);
        }
    }
}

static void fuzz_tj3SaveImage16(const uint8_t *Data, size_t Size) {
    if (Size >= 3 * sizeof(int)) {
        tjhandle handle = tjInitCompress();
        if (handle) {
            const unsigned short *buffer = reinterpret_cast<const unsigned short*>(Data);
            int width = *reinterpret_cast<const int*>(Data);
            int height = *reinterpret_cast<const int*>(Data + sizeof(int));
            int pixelFormat = *reinterpret_cast<const int*>(Data + 2 * sizeof(int));
            tj3SaveImage16(handle, "./dummy_file", buffer, width, 0, height, pixelFormat);
            tjDestroy(handle);
        }
    }
}

static void fuzz_tjSaveImage(const uint8_t *Data, size_t Size) {
    if (Size >= 3 * sizeof(int)) {
        const char *filename = "./dummy_file";
        unsigned char *buffer = const_cast<unsigned char*>(Data);
        int width = *reinterpret_cast<const int*>(Data);
        int height = *reinterpret_cast<const int*>(Data + sizeof(int));
        int pixelFormat = *reinterpret_cast<const int*>(Data + 2 * sizeof(int));
        tjSaveImage(filename, buffer, width, 0, height, pixelFormat, TJFLAG_FASTDCT);
    }
}

static void fuzz_tjLoadImage(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(int)) {
        const char *filename = "./dummy_file";
        int width = 0, height = 0, pixelFormat = 0;
        unsigned char *imageData = tjLoadImage(filename, &width, 0, &height, &pixelFormat, TJFLAG_FASTDCT);
        if (imageData) {
            tjFree(imageData);
        }
    }
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    fuzz_tjAlloc(Data, Size);
    fuzz_tjCompress(Data, Size);
    fuzz_tjDecompress2(Data, Size);
    fuzz_tj3SaveImage16(Data, Size);
    fuzz_tjSaveImage(Data, Size);
    fuzz_tjLoadImage(Data, Size);
    return 0;
}