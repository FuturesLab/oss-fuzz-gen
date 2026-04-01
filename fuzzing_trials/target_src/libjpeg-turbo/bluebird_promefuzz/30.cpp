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

static void fuzz_tjCompressFromYUV(const uint8_t* Data, size_t Size) {
    if (Size < 10) return;

    tjhandle handle = tjInitCompress();
    if (!handle) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int align = 1 << (Data[2] % 3);
    int subsamp = Data[3] % TJSAMP_UNKNOWN;
    int jpegQual = Data[4] % 101;
    int flags = Data[5] % 2;

    unsigned char* jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    size_t yuvSize = tjBufSizeYUV2(width, align, height, subsamp);
    if (yuvSize == (unsigned long)-1 || yuvSize > Size - 6) {
        tjDestroy(handle);
        return;
    }

    const unsigned char* srcBuf = Data + 6;

    tjCompressFromYUV(handle, srcBuf, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    tjFree(jpegBuf);
    tjDestroy(handle);
}

static void fuzz_tjBufSize(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int subsamp = Data[2] % TJSAMP_UNKNOWN;

    tjBufSize(width, height, subsamp);
}

static void fuzz_tjBufSizeYUV2(const uint8_t* Data, size_t Size) {
    if (Size < 4) return;

    int width = Data[0] + 1;
    int align = 1 << (Data[1] % 3);
    int height = Data[2] + 1;
    int subsamp = Data[3] % TJSAMP_UNKNOWN;

    tjBufSizeYUV2(width, align, height, subsamp);
}

static void fuzz_tj3YUVPlaneSize(const uint8_t* Data, size_t Size) {
    if (Size < 5) return;

    int componentID = Data[0] % 3;
    int width = Data[1] + 1;
    int stride = Data[2] + 1;
    int height = Data[3] + 1;
    int subsamp = Data[4] % TJSAMP_UNKNOWN;

    tj3YUVPlaneSize(componentID, width, stride, height, subsamp);
}

static void fuzz_tjPlaneSizeYUV(const uint8_t* Data, size_t Size) {
    if (Size < 5) return;

    int componentID = Data[0] % 3;
    int width = Data[1] + 1;
    int stride = Data[2] + 1;
    int height = Data[3] + 1;
    int subsamp = Data[4] % TJSAMP_UNKNOWN;

    tjPlaneSizeYUV(componentID, width, stride, height, subsamp);
}

static void fuzz_TJBUFSIZEYUV(const uint8_t* Data, size_t Size) {
    if (Size < 3) return;

    int width = Data[0] + 1;
    int height = Data[1] + 1;
    int jpegSubsamp = Data[2] % TJSAMP_UNKNOWN;

    TJBUFSIZEYUV(width, height, jpegSubsamp);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t* Data, size_t Size) {
    fuzz_tjCompressFromYUV(Data, Size);
    fuzz_tjBufSize(Data, Size);
    fuzz_tjBufSizeYUV2(Data, Size);
    fuzz_tj3YUVPlaneSize(Data, Size);
    fuzz_tjPlaneSizeYUV(Data, Size);
    fuzz_TJBUFSIZEYUV(Data, Size);

    return 0;
}