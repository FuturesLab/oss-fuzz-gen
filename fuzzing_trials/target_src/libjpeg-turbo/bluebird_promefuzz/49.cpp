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
#include <cstdlib>
#include <cstring>
#include <iostream>

static tjhandle initializeTurboJPEG() {
    tjhandle handle = tjInitCompress();
    if (!handle) {
        std::cerr << "Failed to initialize TurboJPEG for compression: " << tjGetErrorStr() << std::endl;
        return nullptr;
    }
    return handle;
}

static void cleanupTurboJPEG(tjhandle handle) {
    if (handle) {
        tjDestroy(handle);
    }
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    // Initialize TurboJPEG handle for compression
    tjhandle handle = initializeTurboJPEG();
    if (!handle) return 0;

    // Ensure there is enough data for basic tests
    if (Size < 10) {
        cleanupTurboJPEG(handle);
        return 0;
    }

    // Parameters for tj3YUVBufSize
    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = 1 << (Data[2] % 4);  // 1, 2, 4, or 8
    int subsamp = Data[3] % (TJSAMP_GRAY + 1);

    // Calculate YUV buffer size
    size_t yuvBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (yuvBufSize == 0) {
        cleanupTurboJPEG(handle);
        return 0;
    }

    // Allocate buffers
    unsigned char* yuvBuf = (unsigned char*)malloc(yuvBufSize);
    unsigned char* jpegBuf = nullptr;
    size_t jpegSize = 0;

    if (!yuvBuf) {
        cleanupTurboJPEG(handle);
        return 0;
    }

    // Parameters for tj3CompressFromYUV8
    const unsigned char* srcBuf = Data;
    int jpegWidth = width;
    int jpegHeight = height;

    // Compress from YUV
    if (tj3CompressFromYUV8(handle, srcBuf, jpegWidth, align, jpegHeight, &jpegBuf, &jpegSize) == 0) {
        // Successfully compressed; now try decompressing it back to YUV
        unsigned char* decompressedYUVBuf = (unsigned char*)malloc(yuvBufSize);
        if (decompressedYUVBuf) {
            if (tj3DecompressToYUV8(handle, jpegBuf, jpegSize, decompressedYUVBuf, align) == 0) {
                // Decompression successful
            }
            free(decompressedYUVBuf);
        }
    }

    // Free allocated buffers
    free(yuvBuf);
    if (jpegBuf) tjFree(jpegBuf);

    // Cleanup TurboJPEG handle
    cleanupTurboJPEG(handle);

    return 0;
}