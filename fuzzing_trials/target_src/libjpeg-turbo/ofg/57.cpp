#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;  // Not enough data to process
    }

    tjhandle handle = tjInitCompress();  // Initialize a TurboJPEG compressor handle

    if (handle == NULL) {
        return 0;  // If handle initialization failed, exit early
    }

    int width = 100;  // Example width
    int height = 100; // Example height
    int jpegSubsamp = TJSAMP_444; // Example subsampling
    int jpegQual = 75; // Example quality
    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = NULL;

    // Compress the image
    int result = tjCompress2(handle, data, width, 0, height, TJPF_RGB, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, TJFLAG_FASTDCT);

    if (result != 0) {
        char *errorStr = tjGetErrorStr2(handle);
        if (errorStr != NULL) {
            printf("Error: %s\n", errorStr);
        }
    }

    // Free the JPEG buffer
    if (jpegBuf != NULL) {
        tjFree(jpegBuf);
    }

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}