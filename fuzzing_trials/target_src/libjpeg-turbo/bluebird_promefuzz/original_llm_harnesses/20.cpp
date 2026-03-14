// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjBufSizeYUV at turbojpeg.c:1007:25 in turbojpeg.h
// tjAlloc at turbojpeg.c:883:26 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1157:20 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjBufSize at turbojpeg.c:933:25 in turbojpeg.h
// tjAlloc at turbojpeg.c:883:26 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjAlloc at turbojpeg.c:883:26 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2652:15 in turbojpeg.h
// tjDecompressHeader2 at turbojpeg.c:1903:15 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2724:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
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
#include <cstdio>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0; // Ensure enough data for basic operations

    // Fuzz tjBufSizeYUV
    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int subsamp = Data[2] % 6; // Subsampling format (0-5)
    unsigned long yuvSize = tjBufSizeYUV(width, height, subsamp);

    // Ensure yuvSize is reasonable, avoid excessive allocations
    if (yuvSize == 0 || yuvSize > 10000000) return 0;

    // Fuzz tjAlloc
    unsigned char* buffer = tjAlloc(yuvSize);
    if (!buffer) return 0;

    // Fill the buffer with random data to simulate real image data
    memcpy(buffer, Data + 5, std::min(Size - 5, yuvSize));

    // Fuzz tjCompress
    tjhandle handle = tjInitCompress();
    if (!handle) {
        tjFree(buffer);
        return 0;
    }

    unsigned long compressedSize = tjBufSize(width, height, subsamp);
    unsigned char* compressedBuffer = tjAlloc(compressedSize);
    if (!compressedBuffer) {
        tjDestroy(handle);
        tjFree(buffer);
        return 0;
    }

    int pixelSize = 3; // Assuming RGB
    int pitch = width * pixelSize;
    int jpegQual = Data[3] % 101; // Quality (0-100)
    int flags = Data[4] % 2 ? TJFLAG_FASTDCT : 0;

    tjCompress(handle, buffer, width, pitch, height, TJPF_RGB, compressedBuffer, &compressedSize, subsamp, jpegQual, flags);

    // Fuzz tjDecodeYUVPlanes
    const unsigned char* srcPlanes[3] = {buffer, buffer + width * height, buffer + 2 * width * height};
    int strides[3] = {width, width / 2, width / 2};
    unsigned char* dstBuf = tjAlloc(width * height * pixelSize);
    if (!dstBuf) {
        tjFree(compressedBuffer);
        tjDestroy(handle);
        tjFree(buffer);
        return 0;
    }

    tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, pitch, height, TJPF_RGB, flags);

    // Fuzz tjDecompressHeader2
    int jpegWidth, jpegHeight, jpegSubsamp;
    tjDecompressHeader2(handle, compressedBuffer, compressedSize, &jpegWidth, &jpegHeight, &jpegSubsamp);

    // Fuzz tjDecodeYUV
    tjDecodeYUV(handle, buffer, 1, subsamp, dstBuf, width, pitch, height, TJPF_RGB, flags);

    // Cleanup
    tjFree(dstBuf);
    tjFree(compressedBuffer);
    tjDestroy(handle);
    tjFree(buffer);

    return 0;
}