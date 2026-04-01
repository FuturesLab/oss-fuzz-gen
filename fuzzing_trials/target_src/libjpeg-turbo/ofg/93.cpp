#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle = tjInitDecompress();
    tjscalingfactor scalingFactor;

    // Ensure the size is sufficient to extract scaling factors
    if (size < 2) {
        tjDestroy(handle);
        return 0;
    }

    // Extract scaling factors from the input data
    scalingFactor.num = data[0] % 17 + 1;  // Scaling factors are typically between 1 and 16
    scalingFactor.denom = data[1] % 17 + 1;

    // Call the function-under-test
    int result = tj3SetScalingFactor(handle, scalingFactor);

    // Clean up
    tjDestroy(handle);

    return 0;
}