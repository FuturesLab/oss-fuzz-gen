#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    cmsToneCurve *toneCurve;
    cmsUInt32Number result;

    // Ensure size is sufficient for creating a tone curve with at least one entry
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Calculate the number of entries based on the available data size
    cmsUInt32Number numEntries = size / sizeof(uint16_t);

    // Create a tone curve using the input data
    toneCurve = cmsBuildTabulatedToneCurve16(NULL, numEntries, (const uint16_t *)data);

    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    result = cmsGetToneCurveEstimatedTableEntries(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}