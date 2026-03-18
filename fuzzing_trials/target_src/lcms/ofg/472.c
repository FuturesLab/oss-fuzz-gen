#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_472(const uint8_t *data, size_t size) {
    cmsToneCurve *toneCurve = NULL;

    // Initialize the tone curve with some non-NULL value
    if (size > 0) {
        // Use the data to create a tone curve, ensuring it's non-NULL
        toneCurve = cmsBuildGamma(NULL, data[0] / 255.0 + 1.0); // Normalize to [1.0, 2.0]
    }

    // Call the function-under-test
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}