// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1508:15 in turbojpeg.h
// tj3CompressFromYUVPlanes8 at turbojpeg.c:1259:15 in turbojpeg.h
// tjBufSize at turbojpeg.c:933:25 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tj3DecompressToYUVPlanes8 at turbojpeg.c:2125:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize TurboJPEG handle for compression
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Allocate buffers for YUV planes and JPEG output
    unsigned char *srcPlanes[3] = {nullptr, nullptr, nullptr};
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    int width = 64, height = 64, pixelSize = 3;
    int strides[3] = {width, width / 2, width / 2};
    int jpegSubsamp = TJSAMP_420;
    int jpegQual = 75;
    int flags = 0;

    // Allocate source buffer
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    if (!srcBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Fill source buffer with data
    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * pixelSize)));

    // Allocate destination buffer for YUV planes
    unsigned char *dstPlanes[3];
    dstPlanes[0] = (unsigned char *)malloc(width * height);
    dstPlanes[1] = (unsigned char *)malloc(width * height / 4);
    dstPlanes[2] = (unsigned char *)malloc(width * height / 4);
    if (!dstPlanes[0] || !dstPlanes[1] || !dstPlanes[2]) {
        free(srcBuf);
        if (dstPlanes[0]) free(dstPlanes[0]);
        if (dstPlanes[1]) free(dstPlanes[1]);
        if (dstPlanes[2]) free(dstPlanes[2]);
        tjDestroy(handle);
        return 0;
    }

    // Encode to YUV planes
    if (tj3EncodeYUVPlanes8(handle, srcBuf, width, width * pixelSize, height, TJPF_RGB, dstPlanes, strides) == 0) {
        // Compress from YUV planes to JPEG
        if (tj3CompressFromYUVPlanes8(handle, (const unsigned char * const *)dstPlanes, width, strides, height, &jpegBuf, &jpegSize) == 0) {
            // Use compressed JPEG data in jpegBuf
        }
    }

    // Use tjCompress for direct compression
    unsigned long compressedSize = 0;
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSize(width, height, jpegSubsamp));
    if (dstBuf) {
        if (tjCompress(handle, srcBuf, width, width * pixelSize, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags) == 0) {
            // Use compressed JPEG data in dstBuf
        }
        free(dstBuf);
    }

    // Decompress to YUV planes
    if (jpegBuf) {
        if (tj3DecompressToYUVPlanes8(handle, jpegBuf, jpegSize, dstPlanes, strides) == 0) {
            // Use decompressed YUV data in dstPlanes
        }
        tjFree(jpegBuf);
    }

    // Free allocated resources
    free(srcBuf);
    free(dstPlanes[0]);
    free(dstPlanes[1]);
    free(dstPlanes[2]);
    tjDestroy(handle);

    return 0;
}