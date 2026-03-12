#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a cmsToneCurve
    if (size < sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Allocate memory for tone curve
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(NULL, size / sizeof(cmsFloat32Number), (const cmsUInt16Number *)data);
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIsToneCurveMultisegment(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}