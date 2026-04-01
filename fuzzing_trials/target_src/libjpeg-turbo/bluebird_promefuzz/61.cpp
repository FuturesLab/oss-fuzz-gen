#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include "../src/turbojpeg.h"

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Variables for image dimensions and pixel format
    int width = 0, height = 0, pixelFormat = TJPF_RGB, pitch = 0;
    int flags = 0, align = 1;

    // Allocate memory for tjLoadImage
    unsigned char *imgBuffer = tjLoadImage(filename, &width, align, &height, &pixelFormat, flags);
    if (imgBuffer) {
        // Test tjSaveImage
        tjSaveImage(filename, imgBuffer, width, pitch, height, pixelFormat, flags);
        tjFree(imgBuffer);
    }

    // Create a TurboJPEG instance handle
    tjhandle handle = tjInitDecompress();
    if (handle) {
        // Test tjDecompress2
        unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
        if (dstBuf) {

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 6 of tjDecompress2
            tjDecompress2(handle, Data, Size, dstBuf, width, pitch, -1, pixelFormat, flags);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


            free(dstBuf);
        }
        tjDestroy(handle);
    }

    // Re-create a TurboJPEG instance handle for tj3LoadImage16 and tj3SaveImage16
    handle = tj3Init(TJINIT_COMPRESS);
    if (handle) {
        // Allocate memory for tj3LoadImage16
        int width16 = 0, height16 = 0, pixelFormat16 = TJPF_RGB;
        unsigned short *imgBuffer16 = tj3LoadImage16(handle, filename, &width16, align, &height16, &pixelFormat16);
        if (imgBuffer16) {
            // Test tj3SaveImage16
            tj3SaveImage16(handle, filename, imgBuffer16, width16, pitch, height16, pixelFormat16);
            tj3Free(imgBuffer16);
        }
        tj3Destroy(handle);
    }

    return 0;
}