#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsInt32Number index = 0; // Initialize to 0 for simplicity
    cmsToneCurve *toneCurve = NULL;

    // Ensure size is sufficient for creating a tone curve
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Create a tone curve using the data provided
    toneCurve = cmsBuildTabulatedToneCurve16(NULL, size / sizeof(uint16_t), (const uint16_t *)data);
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    const cmsCurveSegment *segment = cmsGetToneCurveSegment(index, toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}