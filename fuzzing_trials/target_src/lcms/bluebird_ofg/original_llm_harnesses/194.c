#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Initialize a cmsToneCurve object
    cmsToneCurve *originalCurve = cmsBuildGamma(NULL, 2.2); // Example gamma value

    // Ensure the originalCurve is not NULL
    if (originalCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsToneCurve *duplicatedCurve = cmsDupToneCurve(originalCurve);

    // Clean up the allocated resources
    if (duplicatedCurve != NULL) {
        cmsFreeToneCurve(duplicatedCurve);
    }
    cmsFreeToneCurve(originalCurve);

    return 0;
}