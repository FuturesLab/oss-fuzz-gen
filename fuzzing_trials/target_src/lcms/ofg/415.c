#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_415(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0; // Not enough data to create a tone curve
    }

    // Create a tone curve with at least one segment
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(NULL, 2, (const uint16_t *)data);

    if (toneCurve == NULL) {
        return 0; // Failed to create a tone curve
    }

    // Call the function-under-test
    cmsToneCurve *reversedCurve = cmsReverseToneCurve(toneCurve);

    // Clean up
    if (reversedCurve != NULL) {
        cmsFreeToneCurve(reversedCurve);
    }
    cmsFreeToneCurve(toneCurve);

    return 0;
}