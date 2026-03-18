#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create a cmsToneCurve
    if (size < sizeof(cmsCurveSegment)) {
        return 0;
    }

    // Allocate memory for a cmsToneCurve
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(NULL, size / sizeof(cmsCurveSegment), (const cmsUInt16Number *)data);
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIsToneCurveMultisegment(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}