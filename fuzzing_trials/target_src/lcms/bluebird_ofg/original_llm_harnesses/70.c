#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt16Number)) {
        return 0; // Not enough data to create a tone curve
    }

    // Create a tone curve from the input data
    cmsUInt16Number nEntries = *(cmsUInt16Number *)data;
    data += sizeof(cmsUInt16Number);
    size -= sizeof(cmsUInt16Number);

    // Ensure there is enough data for the tone curve entries
    if (size < nEntries * sizeof(cmsUInt16Number)) {
        return 0;
    }

    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(NULL, nEntries, (cmsUInt16Number *)data);
    if (toneCurve == NULL) {
        return 0; // Failed to create tone curve
    }

    // Fuzz the function-under-test
    cmsBool isDescending = cmsIsToneCurveDescending(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}