#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Create a tone curve with a single segment
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurveFloat(NULL, 2, (const cmsFloat32Number *)data);

    // Ensure the tone curve is not NULL
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number entries = cmsGetToneCurveEstimatedTableEntries(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}