// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjGetScalingFactors at turbojpeg.c:1974:28 in turbojpeg.h
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
// tjDecompressHeader3 at turbojpeg.c:1874:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:580:16 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2291:15 in turbojpeg.h
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
#include <cstdio>

static tjscalingfactor getRandomScalingFactor() {
    int numScalingFactors;
    tjscalingfactor *scalingFactors = tjGetScalingFactors(&numScalingFactors);
    if (scalingFactors && numScalingFactors > 0) {
        return scalingFactors[rand() % numScalingFactors];
    }
    tjscalingfactor defaultFactor = {1, 1};
    return defaultFactor;
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize TurboJPEG decompression handle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Set a random scaling factor
    tjscalingfactor scalingFactor = getRandomScalingFactor();
    tj3SetScalingFactor(handle, scalingFactor);

    // Prepare dummy file for JPEG data
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        tj3Destroy(handle);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Decompress the JPEG data to YUV planes
    unsigned char *jpegBuf = const_cast<unsigned char*>(Data);
    unsigned long jpegSize = Size;
    int width = 0, height = 0;
    int subsamp, colorspace;
    if (tjDecompressHeader3(handle, jpegBuf, jpegSize, &width, &height, &subsamp, &colorspace) == -1) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *dstPlanes[3];
    int strides[3];
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = (unsigned char *)malloc(width * height);
        strides[i] = width;
    }

    tjDecompressToYUVPlanes(handle, jpegBuf, jpegSize, dstPlanes, width, strides, height, 0);

    // Clean up
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }
    tj3Destroy(handle);

    return 0;
}