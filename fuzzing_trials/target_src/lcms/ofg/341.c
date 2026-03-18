#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_341(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsInt32Number type = 1; // Example type, can be varied
    cmsFloat64Number params[10]; // Example parameter array

    // Ensure the data is large enough to fill params
    if (size < sizeof(params)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Copy data into params, ensuring no overflow
    for (size_t i = 0; i < sizeof(params) / sizeof(params[0]); i++) {
        params[i] = ((cmsFloat64Number*)data)[i];
    }

    // Call the function under test
    cmsToneCurve *toneCurve = cmsBuildParametricToneCurve(context, type, params);

    // Cleanup
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}