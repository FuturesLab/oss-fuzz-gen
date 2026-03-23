// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
// tjGetScalingFactors at turbojpeg.c:1974:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2006:15 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
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
#include <cstdio>
#include <cstring>

static void handleDecompressToYUVPlanes(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {0, 0, 0};
    int width = 100, height = 100, flags = 0;
    
    // Allocate memory for YUV planes
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = static_cast<unsigned char*>(malloc(width * height));
        if (!dstPlanes[i]) return;
    }

    tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, flags);

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }
}

static void handleSetScalingFactor(tjhandle handle) {
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tjGetScalingFactors(&numScalingFactors);
    if (scalingFactors && numScalingFactors > 0) {
        tj3SetScalingFactor(handle, scalingFactors[0]);
    }
}

static void handleSetCroppingRegion(tjhandle handle) {
    tjregion croppingRegion = {0, 0, 50, 50};
    tj3SetCroppingRegion(handle, croppingRegion);
}

static void handleDecompression(tjhandle handle, const uint8_t *Data, size_t Size) {
    handleSetScalingFactor(handle);
    handleSetCroppingRegion(handle);
    handleDecompressToYUVPlanes(handle, Data, Size);
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    int initType = TJINIT_DECOMPRESS;
    tjhandle handle = tj3Init(initType);
    if (!handle) return 0;

    handleDecompression(handle, Data, Size);

    tjDestroy(handle);
    return 0;
}