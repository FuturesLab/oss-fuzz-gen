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

static tjscalingfactor getRandomScalingFactor() {
    tjscalingfactor factor;
    factor.num = rand() % 8 + 1;  // Random factor between 1/8 and 8/8
    factor.denom = 8;
    return factor;
}

static tjregion getRandomCroppingRegion() {
    tjregion region;
    region.x = rand() % 100;  // Random x starting point
    region.y = rand() % 100;  // Random y starting point
    region.w = rand() % 100;  // Random width
    region.h = rand() % 100;  // Random height
    return region;
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    tjscalingfactor scalingFactor = getRandomScalingFactor();
    if (tj3SetScalingFactor(handle, scalingFactor) == -1) {
        std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    }

    tjregion croppingRegion1 = getRandomCroppingRegion();
    if (tj3SetCroppingRegion(handle, croppingRegion1) == -1) {
        std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    }

    tjregion croppingRegion2 = getRandomCroppingRegion();
    if (tj3SetCroppingRegion(handle, croppingRegion2) == -1) {
        std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    }

    size_t allocSize = 1024;  // Arbitrary size for allocation
    void *buffer = tj3Alloc(allocSize);
    if (!buffer) {
        std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    }

    std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;

    unsigned short *dstBuf = static_cast<unsigned short*>(tj3Alloc(allocSize));
    if (!dstBuf) {
        std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
    } else {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of tj3Decompress16
        if (tj3Decompress16(handle, Data, Size, dstBuf, 1, TJPF_RGB) == -1) {
        // End mutation: Producer.REPLACE_ARG_MUTATOR


            std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
        }
    }

    std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;

    tj3Free(buffer);
    tj3Free(dstBuf);

    tj3Destroy(handle);

    return 0;
}