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

static void handleError(tjhandle handle) {
    const char *errorStr = tj3GetErrorStr(handle);
    if (errorStr) {
        fprintf(stderr, "Error: %s\n", errorStr);
    }
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file for file-based operations
    const char *dummyFile = "./dummy_file";
    FILE *file = fopen(dummyFile, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Initialize TurboJPEG handle
    tjhandle handle = tjInitCompress();
    if (!handle) {
        handleError(handle);
        return 0;
    }

    // Test tjGetErrorStr2
    const char *errorStr2 = tjGetErrorStr2(handle);
    if (errorStr2) {
        printf("tjGetErrorStr2: %s\n", errorStr2);
    }

    // Test tj3GetErrorStr
    const char *errorStr3 = tj3GetErrorStr(handle);
    if (errorStr3) {
        printf("tj3GetErrorStr: %s\n", errorStr3);
    }

    // Allocate buffer for image data
    int width = 10, height = 10, pixelFormat = TJPF_RGB;
    size_t bufferSize = width * height * tjPixelSize[pixelFormat] * sizeof(unsigned short);
    unsigned short *imageBuffer = (unsigned short *)malloc(bufferSize);
    if (!imageBuffer) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(imageBuffer, Data, std::min(Size, bufferSize));

    // Test tj3SaveImage16
    if (tj3SaveImage16(handle, dummyFile, imageBuffer, width, 0, height, pixelFormat) == -1) {
        handleError(handle);
    }

    // Test tj3LoadImage16
    int loadedWidth = 0, loadedHeight = 0, loadedPixelFormat = TJPF_UNKNOWN;
    unsigned short *loadedImage = tj3LoadImage16(handle, dummyFile, &loadedWidth, 1, &loadedHeight, &loadedPixelFormat);
    if (!loadedImage) {
        handleError(handle);
    } else {
        tj3Free(loadedImage);
    }

    // Test tjSaveImage
    size_t bufferSize8 = width * height * tjPixelSize[pixelFormat];
    unsigned char *imageBuffer8 = (unsigned char *)malloc(bufferSize8);
    if (!imageBuffer8) {
        free(imageBuffer);
        tjDestroy(handle);
        return 0;
    }
    memcpy(imageBuffer8, Data, std::min(Size, bufferSize8));

    if (tjSaveImage(dummyFile, imageBuffer8, width, 0, height, pixelFormat, 0) == -1) {
        handleError(handle);
    }

    // Test tjLoadImage
    int loadedWidth8 = 0, loadedHeight8 = 0, loadedPixelFormat8 = TJPF_UNKNOWN;
    unsigned char *loadedImage8 = tjLoadImage(dummyFile, &loadedWidth8, 1, &loadedHeight8, &loadedPixelFormat8, 0);
    if (!loadedImage8) {
        handleError(handle);
    } else {
        free(loadedImage8);
    }

    // Cleanup
    free(imageBuffer);
    free(imageBuffer8);
    tjDestroy(handle);

    return 0;
}