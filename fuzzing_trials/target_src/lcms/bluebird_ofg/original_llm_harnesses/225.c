#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    cmsToneCurve *toneCurve;

    // Check if size is large enough to create a tone curve
    // Since cmsToneCurve is an incomplete type, we cannot use sizeof directly.
    // Instead, we assume an arbitrary minimum size for a valid tone curve data.
    if (size < 4) { // Assuming at least 4 bytes needed for a basic tone curve
        return 0;
    }

    // Create a tone curve using the data provided
    // Assuming the data is a valid representation of a tone curve
    toneCurve = cmsBuildTabulatedToneCurve16(NULL, size / sizeof(uint16_t), (const uint16_t *)data);

    // Call the function-under-test
    if (toneCurve != NULL) {
        cmsBool result = cmsIsToneCurveLinear(toneCurve);
        (void)result; // Suppress unused variable warning
    }

    // Free the tone curve
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}