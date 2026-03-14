#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_471(const uint8_t *data, size_t size) {
    // Initialize the cmsToneCurve pointer
    cmsToneCurve *toneCurve = NULL;

    // Check if the size is sufficient to create a tone curve
    if (size > 0) {
        // Create a tone curve with at least one segment
        toneCurve = cmsBuildGamma(NULL, 2.2);  // Using gamma value 2.2 as an example
    }

    // Call the function-under-test
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}