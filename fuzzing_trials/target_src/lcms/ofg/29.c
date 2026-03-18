#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nEntries = 3; // Example number of entries
    cmsFloat32Number values[3] = {0.0f, 0.5f, 1.0f}; // Example values for the tone curve

    // Ensure the data size is sufficient for the operation
    if (size < sizeof(cmsFloat32Number) * nEntries) {
        return 0;
    }

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurveFloat(context, nEntries, values);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}