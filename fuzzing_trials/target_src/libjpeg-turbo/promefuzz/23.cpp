// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjBufSizeYUV at turbojpeg.c:1007:25 in turbojpeg.h
// tjAlloc at turbojpeg.c:883:26 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjBufSize at turbojpeg.c:933:25 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2724:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0; // Ensure there's enough data for meaningful fuzzing

    // Fuzz tjBufSizeYUV
    int width = Data[0];
    int height = Data[1];
    int subsamp = Data[2] % 6; // Valid subsampling values are 0-5
    unsigned long yuvBufSize = tjBufSizeYUV(width, height, subsamp);

    // Fuzz tjAlloc
    unsigned char *allocatedBuffer = tjAlloc(yuvBufSize);
    if (allocatedBuffer) {
        std::memset(allocatedBuffer, 0, yuvBufSize);
    }

    // Fuzz tjCompress
    tjhandle handle = tjInitCompress();
    if (handle) {
        unsigned long maxCompressedSize = tjBufSize(width, height, subsamp); // Get the maximum size needed
        unsigned char *dstBuf = (unsigned char *)malloc(maxCompressedSize);
        if (dstBuf) {
            unsigned long compressedSize = maxCompressedSize;
            int result = tjCompress(handle, allocatedBuffer, width, 0, height, TJPF_RGB, dstBuf, &compressedSize, subsamp, 75, 0);
            free(dstBuf);
        }
        tjDestroy(handle);
    }

    // Fuzz tjDecodeYUVPlanes
    const unsigned char *srcPlanes[3] = {allocatedBuffer, allocatedBuffer, allocatedBuffer};
    int strides[3] = {width, width / 2, width / 2};
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]); // Ensure enough space for RGB
    if (dstBuf) {
        handle = tjInitDecompress();
        if (handle) {
            int result = tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, 0, height, TJPF_RGB, 0);
            tjDestroy(handle);
        }
        free(dstBuf);
    }

    // Fuzz tjDecompressHeader2
    handle = tjInitDecompress();
    if (handle && Size >= 10) {
        int imgWidth = 0, imgHeight = 0, imgSubsamp = 0;
        int result = tjDecompressHeader2(handle, (unsigned char *)Data, Size, &imgWidth, &imgHeight, &imgSubsamp);
        tjDestroy(handle);
    }

    // Fuzz tjDecodeYUV
    handle = tjInitDecompress();
    if (handle) {
        dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]); // Ensure enough space for RGB
        if (dstBuf) {
            int result = tjDecodeYUV(handle, allocatedBuffer, 1, subsamp, dstBuf, width, 0, height, TJPF_RGB, 0);
            free(dstBuf);
        }
        tjDestroy(handle);
    }

    // Cleanup
    if (allocatedBuffer) {
        tjFree(allocatedBuffer);
    }

    return 0;
}