// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1808:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2006:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2006:15 in turbojpeg.h
// tj3Alloc at turbojpeg.c:877:17 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Decompress16 at turbojpeg-mp.c:148:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:618:17 in turbojpeg.h
// tj3Free at turbojpeg.c:890:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
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

static tjscalingfactor getRandomScalingFactor() {
    tjscalingfactor scalingFactor;
    scalingFactor.num = 1 + (rand() % 8);
    scalingFactor.denom = 8;
    return scalingFactor;
}

static tjregion getRandomCroppingRegion() {
    tjregion region;
    region.x = rand() % 100;
    region.y = rand() % 100;
    region.w = 10 + (rand() % 90);
    region.h = 10 + (rand() % 90);
    return region;
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    // Step 1: Set scaling factor
    tjscalingfactor scalingFactor = getRandomScalingFactor();
    tj3SetScalingFactor(handle, scalingFactor);

    // Step 2: Set cropping region
    tjregion region1 = getRandomCroppingRegion();
    tj3SetCroppingRegion(handle, region1);

    // Step 3: Set another cropping region
    tjregion region2 = getRandomCroppingRegion();
    tj3SetCroppingRegion(handle, region2);

    // Step 4: Allocate memory
    void *buffer = tj3Alloc(Size);

    // Step 5: Get error string
    char *errorStr1 = tj3GetErrorStr(handle);

    // Step 6: Get error string again
    char *errorStr2 = tj3GetErrorStr(handle);

    // Step 7: Decompress
    unsigned short *dstBuf = new unsigned short[Size / sizeof(unsigned short)];
    tj3Decompress16(handle, Data, Size, dstBuf, 0, TJPF_RGB);

    // Step 8: Get error string after decompression
    char *errorStr3 = tj3GetErrorStr(handle);

    // Step 9: Free allocated memory
    tj3Free(buffer);

    // Step 10: Free destination buffer
    delete[] dstBuf;

    // Step 11: Destroy handle
    tj3Destroy(handle);

    return 0;
}