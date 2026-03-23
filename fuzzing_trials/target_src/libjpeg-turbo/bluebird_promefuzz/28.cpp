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
#include <fstream>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    std::ofstream ofs("./dummy_file", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz TJBUFSIZE
    int width = Data[0];
    int height = (Size > 1) ? Data[1] : 1;
    try {
        unsigned long bufSize = TJBUFSIZE(width, height);
    } catch (...) {
        // Handle exceptions if necessary
    }

    // Fuzz tjDecompressToYUVPlanes
    if (Size >= 4) {
        tjhandle handle = tjInitDecompress();
        unsigned char *jpegBuf = const_cast<unsigned char*>(Data);
        unsigned long jpegSize = Size;
        int outWidth = Data[2];
        int outHeight = Data[3];
        unsigned char *dstPlanes[3] = { nullptr, nullptr, nullptr };
        int strides[3] = { 0, 0, 0 };
        int flags = 0;

        if (handle) {
            tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, outWidth, strides, outHeight, flags);
            tjDestroy(handle);
        }
    }

    // Fuzz tj3YUVPlaneHeight
    int componentID = Data[0] % 3;
    int subsamp = (Size > 1) ? Data[1] % 4 : 0;
    try {
        int planeHeight = tj3YUVPlaneHeight(componentID, height, subsamp);
    } catch (...) {
        // Handle exceptions if necessary
    }

    // Fuzz tjDecompressHeader2
    if (Size >= 3) {
        tjhandle handle = tjInitDecompress();
        unsigned char *jpegBuf = const_cast<unsigned char*>(Data);
        unsigned long jpegSize = Size;
        int width = 0, height = 0, jpegSubsamp = 0;

        if (handle) {
            tjDecompressHeader2(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp);
            tjDestroy(handle);
        }
    }

    // Fuzz tjCompress
    if (Size >= 6) {
        tjhandle handle = tjInitCompress();
        unsigned char *srcBuf = const_cast<unsigned char*>(Data);
        int width = Data[0];
        int pitch = width * 3;
        int height = Data[1];
        int pixelSize = 3;
        unsigned char *dstBuf = nullptr;
        unsigned long compressedSize = 0;
        int jpegSubsamp = Data[2] % 4;
        int jpegQual = Data[3] % 101;
        int flags = 0;

        if (handle) {
            tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);
            tjDestroy(handle);
        }
    }

    // Fuzz tjBufSizeYUV
    if (Size >= 3) {
        int subsamp = Data[2] % 4;
        try {
            unsigned long yuvBufSize = tjBufSizeYUV(width, height, subsamp);
        } catch (...) {
            // Handle exceptions if necessary
        }
    }

    return 0;
}