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
#include <cstdio>
#include <cstring>

static void handleDecompressToYUVPlanes(tjhandle handle, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }
    
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {0, 0, 0};
    int width = 100, height = 100, flags = 0;
    
    // Allocate memory for YUV planes
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = static_cast<unsigned char*>(malloc(width * height));
        if (!dstPlanes[i]) {
                return;
        }
    }

    tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, flags);

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }
}

static void handleSetScalingFactor(tjhandle handle) {
    int numScalingFactors = 0;

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjGetScalingFactors with tj3GetScalingFactors
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    int initType = TJINIT_DECOMPRESS;
    tjhandle handle = tj3Init(initType);
    if (!handle) {
        return 0;
    }

    handleDecompression(handle, Data, Size);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjDestroy with tj3GetErrorCode
    tj3GetErrorCode(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}