// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjLoadImage at turbojpeg.c:3107:26 in turbojpeg.h
// tjSaveImage at turbojpeg.c:3128:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2059:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3LoadImage16 at turbojpeg-mp.c:434:21 in turbojpeg.h
// tj3SaveImage16 at turbojpeg-mp.c:487:15 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <turbojpeg.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
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
            tjDecompress2(handle, Data, Size, dstBuf, width, pitch, height, pixelFormat, flags);
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