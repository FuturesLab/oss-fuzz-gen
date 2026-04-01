// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:538:20 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1959:28 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1981:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:601:15 in turbojpeg.h
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
#include <iostream>
#include <fstream>
#include <cstring>

static void WriteDummyFile(const uint8_t *Data, size_t Size) {
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char *>(Data), Size);
        outFile.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a TurboJPEG decompressor instance
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Retrieve scaling factors
    int numScalingFactors = 0;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    if (!scalingFactors || numScalingFactors == 0) {
        tjDestroy(handle);
        return 0;
    }

    // Set a scaling factor (use the first available one)
    tjscalingfactor factor = scalingFactors[0];
    if (tj3SetScalingFactor(handle, factor) == -1) {
        tjDestroy(handle);
        return 0;
    }

    // Prepare dummy JPEG data
    WriteDummyFile(Data, Size);

    // Prepare YUV planes and strides
    unsigned char *dstPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {0, 0, 0};
    int width = 0, height = 0; // These should be set to valid dimensions

    // Attempt to decompress to YUV planes
    int result = tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, 0);

    // Clean up resources
    if (result == 0) {
        for (int i = 0; i < 3; ++i) {
            free(dstPlanes[i]);
        }
    }

    tjDestroy(handle);
    return 0;
}