// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1235:15 in turbojpeg.h
// tjFree at turbojpeg.c:896:16 in turbojpeg.h
// tjGetScalingFactors at turbojpeg.c:1974:28 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1959:28 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1959:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
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
#include <cstring>
#include <cstdio>
#include <cstdlib>

static void fuzz_tjCompress(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    int width = 100, height = 100, pixelSize = 3;
    int pitch = width * pixelSize;
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    if (!srcBuf) return;

    memcpy(srcBuf, Data, width * height * pixelSize < Size ? width * height * pixelSize : Size);

    unsigned long compressedSize = 0;
    unsigned char *dstBuf = nullptr;
    int jpegSubsamp = TJSAMP_444, jpegQual = 75, flags = 0;

    tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);

    free(srcBuf);
    if (dstBuf) tjFree(dstBuf);
}

static void fuzz_tjGetScalingFactors() {
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tjGetScalingFactors(&numScalingFactors);
    // Use scalingFactors and numScalingFactors if needed
}

static void fuzz_tj3GetScalingFactors() {
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    // Use scalingFactors and numScalingFactors if needed
}

static void fuzz_tj3Init(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    int initType = TJINIT_COMPRESS;
    if (Size > 0) {
        initType = Data[0] % 3; // Randomly choose between 0, 1, 2
    }

    tjhandle handle = tj3Init(initType);
    if (handle) {
        fuzz_tjCompress(handle, Data, Size);
        tjDestroy(handle);
    }
}

static void fuzz_tj3SetScalingFactor(tjhandle handle) {
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    if (scalingFactors && numScalingFactors > 0) {
        tj3SetScalingFactor(handle, scalingFactors[0]);
    }
}

static void fuzz_tjDecompressToYUVPlanes(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    unsigned long jpegSize = Size;
    const unsigned char *jpegBuf = Data;
    int width = 100, height = 100;
    unsigned char *dstPlanes[3];
    int strides[3] = {width, width / 2, width / 2};
    unsigned char *yuvBuffer = (unsigned char *)malloc(width * height * 3 / 2);
    if (!yuvBuffer) return;

    dstPlanes[0] = yuvBuffer;
    dstPlanes[1] = yuvBuffer + width * height;
    dstPlanes[2] = yuvBuffer + width * height * 5 / 4;

    int flags = 0;
    tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, width, strides, height, flags);

    free(yuvBuffer);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    fuzz_tjGetScalingFactors();
    fuzz_tj3GetScalingFactors();
    fuzz_tj3Init(Data, Size);

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle) {
        fuzz_tj3SetScalingFactor(handle);
        fuzz_tjDecompressToYUVPlanes(handle, Data, Size);
        tjDestroy(handle);
    }

    return 0;
}