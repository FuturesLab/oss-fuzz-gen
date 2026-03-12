#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"

    int tj3SetScalingFactor(tjhandle handle, tjscalingfactor scalingFactor);
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(tjscalingfactor)) {
        return 0;
    }

    // Initialize a TurboJPEG handle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == nullptr) {
        return 0;
    }

    // Extract a tjscalingfactor from the input data
    tjscalingfactor scalingFactor;
    scalingFactor.num = data[0] + 1; // Ensure non-zero
    scalingFactor.denom = data[1] + 1; // Ensure non-zero

    // Call the function under test
    tj3SetScalingFactor(handle, scalingFactor);

    // Clean up
    tj3Destroy(handle);

    return 0;
}