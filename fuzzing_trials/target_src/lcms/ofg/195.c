#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a tone curve
    if (size < sizeof(cmsUInt16Number) * 2) {
        return 0;
    }

    // Create a tone curve with at least two points
    cmsUInt16Number points[2];
    points[0] = data[0] | (data[1] << 8);
    points[1] = data[2] | (data[3] << 8);

    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(NULL, 2, points);

    if (toneCurve != NULL) {
        // Call the function-under-test
        const cmsUInt16Number *estimatedTable = cmsGetToneCurveEstimatedTable(toneCurve);

        // Use the estimatedTable for further processing or validation if needed
        // (For fuzzing purposes, we don't need to do anything specific here)

        // Free the tone curve after use
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}