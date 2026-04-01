#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there's at least some data

    // Initialize TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        std::cerr << "Failed to initialize TurboJPEG decompressor" << std::endl;
        return 0;
    }

    // Allocate memory for the output YUV buffer
    int width = 128;  // Example width
    int height = 128; // Example height
    int yuvSize = tjBufSizeYUV2(width, 4, height, TJSAMP_420);
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (!yuvBuffer) {
        std::cerr << "Failed to allocate YUV buffer" << std::endl;
        tjDestroy(handle);
        return 0;
    }

    // Call the function under test
    int result = tjDecompressToYUV(handle, (unsigned char *)data, (unsigned long)size, yuvBuffer, 4);

    // Clean up
    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}