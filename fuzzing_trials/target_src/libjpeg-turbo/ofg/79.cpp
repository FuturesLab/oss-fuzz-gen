#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    tjscalingfactor scalingFactor;

    // Ensure data and size are sufficient to define scaling factors
    if (size < 2) {
        tj3Destroy(handle);
        return 0;
    }

    // Set scaling factor values using data
    scalingFactor.num = data[0] % 17 + 1;  // Ensure non-zero and within a reasonable range
    scalingFactor.denom = data[1] % 17 + 1; // Ensure non-zero and within a reasonable range

    // Call the function-under-test
    tj3SetScalingFactor(handle, scalingFactor);

    // Clean up
    tj3Destroy(handle);

    return 0;
}