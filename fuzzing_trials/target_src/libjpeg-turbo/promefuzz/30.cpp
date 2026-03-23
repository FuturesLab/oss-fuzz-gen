// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1959:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
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
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a TurboJPEG decompression instance
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Scaling factors
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);

    if (scalingFactors && numScalingFactors > 0) {
        // Choose a scaling factor from the available ones
        tjscalingfactor scalingFactor = scalingFactors[0];

        // Set the scaling factor
        tj3SetScalingFactor(handle, scalingFactor);
    }

    // Decompress to YUV planes
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {0, 0, 0};
    int width = 0, height = 0;

    // Dummy values for width and height
    width = 128;
    height = 128;
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Allocate memory for YUV planes
    dstPlanes[0] = (unsigned char *)malloc(width * height);
    dstPlanes[1] = (unsigned char *)malloc((width / 2) * (height / 2));
    dstPlanes[2] = (unsigned char *)malloc((width / 2) * (height / 2));

    if (dstPlanes[0] && dstPlanes[1] && dstPlanes[2]) {
        tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, 0);
    }

    // Clean up
    free(dstPlanes[0]);
    free(dstPlanes[1]);
    free(dstPlanes[2]);
    tjDestroy(handle);

    return 0;
}