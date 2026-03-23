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
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    // Fuzz tjSaveImage
    if (Size > 100) {
        const char *filename = "./dummy_file";
        int width = 10;
        int pitch = width * 3; // Assuming pixelFormat is RGB
        int height = 10;
        int pixelFormat = TJPF_RGB;
        int flags = 0;

        // Ensure the buffer is large enough
        size_t bufferSize = height * pitch;
        if (Size >= bufferSize) {
            unsigned char *buffer = (unsigned char*)malloc(bufferSize);
            memcpy(buffer, Data, bufferSize);

            FILE *file = fopen(filename, "wb");
            if (file) {
                fwrite(buffer, 1, bufferSize, file);
                fclose(file);
            }

            tjSaveImage(filename, buffer, width, pitch, height, pixelFormat, flags);
            free(buffer);
        }
    }

    // Fuzz tjDecompressHeader3
    if (Size > 12) {
        tjhandle handle = tjInitDecompress();
        const unsigned char *jpegBuf = Data;
        unsigned long jpegSize = Size;
        int width, height, jpegSubsamp, jpegColorspace;

        tjDecompressHeader3(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp, &jpegColorspace);
        tjDestroy(handle);
    }

    // Fuzz tjEncodeYUVPlanes
    if (Size > 30) {
        tjhandle handle = tjInitCompress();
        const unsigned char *srcBuf = Data;
        int width = 10;
        int pitch = width * 3; // Assuming pixelFormat is RGB
        int height = 10;
        int pixelFormat = TJPF_RGB;
        unsigned char *dstPlanes[3] = { nullptr, nullptr, nullptr };
        int strides[3] = { width, width / 2, width / 2 };
        int subsamp = TJSAMP_420;
        int flags = 0;

        tjEncodeYUVPlanes(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, strides, subsamp, flags);
        tjDestroy(handle);
    }

    // Fuzz tjDecompress
    if (Size > 15) {
        tjhandle handle = tjInitDecompress();
        unsigned char *jpegBuf = const_cast<unsigned char*>(Data);
        unsigned long jpegSize = Size;
        unsigned char *dstBuf = (unsigned char*)malloc(10 * 10 * 3); // Assuming output is RGB
        int width = 10;
        int pitch = width * 3;
        int height = 10;
        int pixelSize = 3;
        int flags = 0;

        tjDecompress(handle, jpegBuf, jpegSize, dstBuf, width, pitch, height, pixelSize, flags);
        free(dstBuf);
        tjDestroy(handle);
    }

    // Fuzz tjCompress
    if (Size > 20) {
        tjhandle handle = tjInitCompress();
        unsigned char *srcBuf = const_cast<unsigned char*>(Data);
        int width = 10;
        int pitch = width * 3;
        int height = 10;
        int pixelSize = 3;
        unsigned char *dstBuf = nullptr;
        unsigned long compressedSize = 0;
        int jpegSubsamp = TJSAMP_420;
        int jpegQual = 75;
        int flags = 0;

        tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);
        tjDestroy(handle);
        tjFree(dstBuf);
    }

    // Fuzz tjDecompress2
    if (Size > 25) {
        tjhandle handle = tjInitDecompress();
        const unsigned char *jpegBuf = Data;
        unsigned long jpegSize = Size;
        unsigned char *dstBuf = (unsigned char*)malloc(10 * 10 * 3); // Assuming output is RGB
        int width = 10;
        int pitch = width * 3;
        int height = 10;
        int pixelFormat = TJPF_RGB;
        int flags = 0;

        tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, pitch, height, pixelFormat, flags);
        free(dstBuf);
        tjDestroy(handle);
    }

    return 0;
}