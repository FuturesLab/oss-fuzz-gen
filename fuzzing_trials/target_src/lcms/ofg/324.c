#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_324(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nEntries = 256; // Example size for tone curve entries
    cmsUInt16Number *toneCurveEntries = (cmsUInt16Number *)malloc(nEntries * sizeof(cmsUInt16Number));

    if (toneCurveEntries == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Ensure the data size is sufficient to fill the tone curve entries
    if (size < nEntries * sizeof(cmsUInt16Number)) {
        free(toneCurveEntries);
        cmsDeleteContext(context);
        return 0;
    }

    // Copy data into toneCurveEntries
    for (cmsUInt32Number i = 0; i < nEntries; i++) {
        toneCurveEntries[i] = ((cmsUInt16Number *)data)[i];
    }

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(context, nEntries, toneCurveEntries);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    free(toneCurveEntries);
    cmsDeleteContext(context);

    return 0;
}