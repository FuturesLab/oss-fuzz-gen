// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:999:25 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1476:15 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjEncodeYUV at turbojpeg.c:1767:15 in turbojpeg.h
// tjEncodeYUVPlanes at turbojpeg.c:1663:15 in turbojpeg.h
// tjEncodeYUV3 at turbojpeg.c:1734:15 in turbojpeg.h
// tjBufSize at turbojpeg.c:933:25 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
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
#include <iostream>
#include <fstream>

static void writeFile(const char* filename, const uint8_t* data, size_t size) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(data), size);
        file.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 256; // Example width
    int height = 256; // Example height
    int subsamp = TJSAMP_420; // Example subsampling
    int jpegQual = 75; // Example quality
    int flags = 0; // Example flags

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    int align = 1; // Example alignment

    // Prepare a dummy YUV buffer
    size_t yuvSize = tjBufSizeYUV2(width, align, height, subsamp);
    unsigned char *yuvBuf = (unsigned char *)malloc(yuvSize);
    if (!yuvBuf) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(yuvBuf, Data, std::min(Size, yuvSize));

    // Fuzz tjCompressFromYUV
    tjCompressFromYUV(handle, yuvBuf, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Fuzz tjDecompressToYUVPlanes if jpegBuf is valid
    if (jpegBuf) {
        unsigned char *dstPlanes[3] = { nullptr, nullptr, nullptr };
        int strides[3] = { width, width / 2, width / 2 };
        for (int i = 0; i < 3; i++) {
            dstPlanes[i] = (unsigned char *)malloc(strides[i] * height / (i == 0 ? 1 : 2));
        }
        tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, width, strides, height, flags);
        for (int i = 0; i < 3; i++) {
            free(dstPlanes[i]);
        }
        tjFree(jpegBuf);
    }

    // Fuzz tjEncodeYUV
    unsigned char *dstBuf = (unsigned char *)malloc(yuvSize);
    if (dstBuf) {
        tjEncodeYUV(handle, yuvBuf, width, width, height, 3, dstBuf, subsamp, flags);
        free(dstBuf);
    }

    // Fuzz tjEncodeYUVPlanes
    unsigned char *dstPlanes2[3] = { nullptr, nullptr, nullptr };
    int strides2[3] = { width, width / 2, width / 2 };
    for (int i = 0; i < 3; i++) {
        dstPlanes2[i] = (unsigned char *)malloc(strides2[i] * height / (i == 0 ? 1 : 2));
    }
    tjEncodeYUVPlanes(handle, yuvBuf, width, width, height, TJPF_RGB, dstPlanes2, strides2, subsamp, flags);
    for (int i = 0; i < 3; i++) {
        free(dstPlanes2[i]);
    }

    // Fuzz tjEncodeYUV3
    dstBuf = (unsigned char *)malloc(yuvSize);
    if (dstBuf) {
        tjEncodeYUV3(handle, yuvBuf, width, width, height, TJPF_RGB, dstBuf, align, subsamp, flags);
        free(dstBuf);
    }

    // Fuzz tjCompress
    unsigned long maxCompressedSize = tjBufSize(width, height, subsamp);
    unsigned char *compressedBuf = (unsigned char *)malloc(maxCompressedSize);
    if (compressedBuf) {
        tjCompress(handle, yuvBuf, width, width, height, 3, compressedBuf, &jpegSize, subsamp, jpegQual, flags);
        free(compressedBuf);
    }

    free(yuvBuf);
    tjDestroy(handle);
    return 0;
}