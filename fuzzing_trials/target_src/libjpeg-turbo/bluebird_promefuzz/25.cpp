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

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
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
        if (tj3Decompress16(handle, Data, Size, dstBuf, 0, TJPF_RGB) == -1) {
            std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;
        }
    }

    std::cerr << "Error: " << tj3GetErrorStr(handle) << std::endl;

    tj3Free(buffer);
    tj3Free(dstBuf);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tj3Free to tj3SaveImage12
    tjhandle ret_tjInitCompress_tlwlo = tjInitCompress();
    int ret_tj3GetErrorCode_daczb = tj3GetErrorCode(0);
    if (ret_tj3GetErrorCode_daczb < 0){
    	return 0;
    }
    int bwxvbanz = 64;
    tjscalingfactor* ret_tjGetScalingFactors_coths = tjGetScalingFactors(&bwxvbanz);
    if (ret_tjGetScalingFactors_coths == NULL){
    	return 0;
    }
    int ywszqani = 1;
    tjscalingfactor* ret_tj3GetScalingFactors_mgcij = tj3GetScalingFactors(&ywszqani);
    if (ret_tj3GetScalingFactors_mgcij == NULL){
    	return 0;
    }

    int ret_tj3SaveImage12_djmbz = tj3SaveImage12(ret_tjInitCompress_tlwlo, (const char *)buffer, NULL, TJXOPT_PROGRESSIVE, ret_tj3GetErrorCode_daczb, bwxvbanz, ywszqani);
    if (ret_tj3SaveImage12_djmbz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tj3Destroy(handle);

    return 0;
}