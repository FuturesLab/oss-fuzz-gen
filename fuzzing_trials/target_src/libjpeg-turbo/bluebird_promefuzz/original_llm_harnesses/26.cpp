// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjGetScalingFactors at turbojpeg.c:1974:28 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1959:28 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2006:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
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
#include <fstream>
#include <iostream>

static void fuzz_tjGetScalingFactors() {
    int numScalingFactors = 0;
    tjscalingfactor *factors = tjGetScalingFactors(&numScalingFactors);
    if (factors) {
        for (int i = 0; i < numScalingFactors; ++i) {
            // Access scaling factors (factors[i].num, factors[i].denom)
        }
    }
}

static void fuzz_tj3GetScalingFactors() {
    int numScalingFactors = 0;
    tjscalingfactor *factors = tj3GetScalingFactors(&numScalingFactors);
    if (factors) {
        for (int i = 0; i < numScalingFactors; ++i) {
            // Access scaling factors (factors[i].num, factors[i].denom)
        }
    }
}

static void fuzz_tj3InitAndSetCroppingRegion(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tjregion)) return;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return;

    tjregion region;
    std::memcpy(&region, Data, sizeof(tjregion));

    int result = tj3SetCroppingRegion(handle, region);
    if (result != 0) {
        // Handle error
    }

    tjDestroy(handle);
}

static void fuzz_tj3SetScalingFactor(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tjscalingfactor)) return;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return;

    tjscalingfactor factor;
    std::memcpy(&factor, Data, sizeof(tjscalingfactor));

    int result = tj3SetScalingFactor(handle, factor);
    if (result != 0) {
        // Handle error
    }

    tjDestroy(handle);
}

static void fuzz_tjDecompressToYUVPlanes(const uint8_t *Data, size_t Size) {
    if (Size < 4) return;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return;

    unsigned long jpegSize = Size;
    unsigned char *jpegBuf = const_cast<unsigned char*>(Data);

    int width = 1, height = 1; // Minimal dimensions for fuzzing
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {width, width / 2, width / 2};
    int flags = 0;

    int result = tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, width, strides, height, flags);
    if (result != 0) {
        // Handle error
    }

    tjDestroy(handle);
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    fuzz_tjGetScalingFactors();
    fuzz_tj3GetScalingFactors();
    fuzz_tj3InitAndSetCroppingRegion(Data, Size);
    fuzz_tj3SetScalingFactor(Data, Size);
    fuzz_tjDecompressToYUVPlanes(Data, Size);

    return 0;
}