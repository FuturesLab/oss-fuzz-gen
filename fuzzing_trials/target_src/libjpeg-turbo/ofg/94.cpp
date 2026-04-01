#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract necessary values
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Initialize tjhandle and tjscalingfactor
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Extract scaling factor numerator and denominator from data
    int num = ((int*)data)[0] % 17 + 1;  // Ensure numerator is between 1 and 16
    int denom = ((int*)data)[1] % 17 + 1; // Ensure denominator is between 1 and 16

    // Create a tjscalingfactor struct
    tjscalingfactor scalingFactor;
    scalingFactor.num = num;
    scalingFactor.denom = denom;

    // Call the function-under-test
    tj3SetScalingFactor(handle, scalingFactor);

    // Clean up
    tjDestroy(handle);

    return 0;
}