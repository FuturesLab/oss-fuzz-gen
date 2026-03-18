#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nEntries = 256; // A reasonable number of entries for a tone curve
    cmsFloat32Number toneCurveEntries[256];

    // Ensure the size is sufficient to fill the toneCurveEntries array
    if (size < nEntries * sizeof(cmsFloat32Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Fill the toneCurveEntries array with data
    for (cmsUInt32Number i = 0; i < nEntries; i++) {
        toneCurveEntries[i] = ((const cmsFloat32Number*)data)[i];
    }

    // Call the function under test
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurveFloat(context, nEntries, toneCurveEntries);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}