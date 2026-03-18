// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:636:17 in turbojpeg.h
// tjGetErrorStr2 at turbojpeg.c:630:17 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2059:15 in turbojpeg.h
// tjDecompress at turbojpeg.c:2111:15 in turbojpeg.h
// tjSaveImage at turbojpeg.c:3128:15 in turbojpeg.h
// tjLoadImage at turbojpeg.c:3107:26 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
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

static void test_tjGetErrorStr() {
    char *errorStr = tjGetErrorStr();
    if (errorStr) {
        printf("tjGetErrorStr: %s\n", errorStr);
    }
}

static void test_tjGetErrorStr2(tjhandle handle) {
    char *errorStr = tjGetErrorStr2(handle);
    if (errorStr) {
        printf("tjGetErrorStr2: %s\n", errorStr);
    }
}

static void test_tjDecompress2(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Need at least some data for a JPEG buffer
    int width = 100, height = 100, pitch = 0, pixelFormat = TJPF_RGB, flags = 0;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!dstBuf) return;

    int result = tjDecompress2(handle, Data, Size, dstBuf, width, pitch, height, pixelFormat, flags);
    if (result == 0) {
        printf("tjDecompress2 succeeded.\n");
    } else {
        test_tjGetErrorStr2(handle);
    }
    free(dstBuf);
}

static void test_tjDecompress(tjhandle handle, uint8_t *jpegBuf, size_t jpegSize) {
    int width = 100, height = 100, pitch = 0, pixelSize = tjPixelSize[TJPF_RGB], flags = 0;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * pixelSize);
    if (!dstBuf) return;

    int result = tjDecompress(handle, jpegBuf, jpegSize, dstBuf, width, pitch, height, pixelSize, flags);
    if (result == 0) {
        printf("tjDecompress succeeded.\n");
    } else {
        test_tjGetErrorStr2(handle);
    }
    free(dstBuf);
}

static void test_tjSaveImage(const uint8_t *Data, size_t Size) {
    int width = 100, height = 100, pitch = width * tjPixelSize[TJPF_RGB], pixelFormat = TJPF_RGB, flags = 0;
    size_t bufferSize = pitch * height;
    if (Size < bufferSize) return;
    
    unsigned char *buffer = (unsigned char *)malloc(bufferSize);
    if (!buffer) return;
    memcpy(buffer, Data, bufferSize);

    int result = tjSaveImage("./dummy_file", buffer, width, pitch, height, pixelFormat, flags);
    if (result == 0) {
        printf("tjSaveImage succeeded.\n");
    } else {
        test_tjGetErrorStr();
    }
    free(buffer);
}

static void test_tjLoadImage() {
    int width = 0, height = 0, pixelFormat = 0, flags = 0;
    unsigned char *imageData = tjLoadImage("./dummy_file", &width, 1, &height, &pixelFormat, flags);
    if (imageData) {
        printf("tjLoadImage succeeded.\n");
        tjFree(imageData);
    } else {
        test_tjGetErrorStr();
    }
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        test_tjGetErrorStr();
        return 0;
    }

    test_tjGetErrorStr();
    test_tjGetErrorStr2(handle);
    test_tjDecompress2(handle, Data, Size);
    test_tjDecompress(handle, const_cast<uint8_t*>(Data), Size);
    test_tjSaveImage(Data, Size);
    test_tjLoadImage();

    tjDestroy(handle);
    return 0;
}