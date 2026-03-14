#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_323(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nEntries = 256; // Example size for the tone curve
    cmsUInt16Number toneCurveEntries[256];

    // Initialize toneCurveEntries with non-NULL values
    for (cmsUInt32Number i = 0; i < nEntries; i++) {
        toneCurveEntries[i] = (cmsUInt16Number)(i * 256); // Example initialization
    }

    if (size >= sizeof(cmsUInt16Number) * nEntries) {
        // Use the provided data to fill the toneCurveEntries
        for (cmsUInt32Number i = 0; i < nEntries; i++) {
            toneCurveEntries[i] = ((const cmsUInt16Number *)data)[i];
        }
    }

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(context, nEntries, toneCurveEntries);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}