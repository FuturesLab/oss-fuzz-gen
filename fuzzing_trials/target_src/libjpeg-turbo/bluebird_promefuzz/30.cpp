#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../src/turbojpeg.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>

static void fuzzTJBUFSIZE(int width, int height) {
    try {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of TJBUFSIZE
        unsigned long bufferSize = TJBUFSIZE(width, TJ_NUMINIT);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    } catch (const std::exception &e) {
        // Handle any exception thrown by TJBUFSIZE
    }
}

static void fuzzTjDecompressHeader2(tjhandle handle, unsigned char *jpegBuf, unsigned long jpegSize) {
    int width = 0, height = 0, jpegSubsamp = 0;
    try {
        int res = tjDecompressHeader2(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp);
    } catch (const std::exception &e) {
        // Handle any exception thrown by tjDecompressHeader2
    }
}

static void fuzzTjDecompress2(tjhandle handle, const unsigned char *jpegBuf, unsigned long jpegSize) {
    int width = 100, height = 100, pixelFormat = TJPF_RGB, flags = 0;
    unsigned char *dstBuf = new unsigned char[width * height * tjPixelSize[pixelFormat]];
    try {
        int res = tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, 0, height, pixelFormat, flags);
    } catch (const std::exception &e) {
        // Handle any exception thrown by tjDecompress2
    }
    delete[] dstBuf;
}

static void fuzzTj3JPEGBufSize(int width, int height, int jpegSubsamp) {
    try {
        size_t bufferSize = tj3JPEGBufSize(width, height, jpegSubsamp);
    } catch (const std::exception &e) {
        // Handle any exception thrown by tj3JPEGBufSize
    }
}

static void fuzzTj3DecompressHeader(tjhandle handle, const unsigned char *jpegBuf, size_t jpegSize) {
    try {
        int res = tj3DecompressHeader(handle, jpegBuf, jpegSize);
    } catch (const std::exception &e) {
        // Handle any exception thrown by tj3DecompressHeader
    }
}

static void fuzzTjDecompressHeader3(tjhandle handle, const unsigned char *jpegBuf, unsigned long jpegSize) {
    int width = 0, height = 0, jpegSubsamp = 0, jpegColorspace = 0;
    try {
        int res = tjDecompressHeader3(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp, &jpegColorspace);
    } catch (const std::exception &e) {
        // Handle any exception thrown by tjDecompressHeader3
    }
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Fuzz each function with random data
    fuzzTJBUFSIZE(Data[0], Data[0]);
    fuzzTjDecompressHeader2(handle, const_cast<unsigned char*>(Data), Size);
    fuzzTjDecompress2(handle, Data, Size);
    fuzzTj3JPEGBufSize(Data[0], Data[0], Data[0]);
    fuzzTj3DecompressHeader(handle, Data, Size);
    fuzzTjDecompressHeader3(handle, Data, Size);

    tjDestroy(handle);
    return 0;
}