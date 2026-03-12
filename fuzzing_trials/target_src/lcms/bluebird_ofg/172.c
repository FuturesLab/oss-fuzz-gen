#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract parameters
    if (size < sizeof(cmsInt32Number) + sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Extract cmsInt32Number from data
    cmsInt32Number type = *(const cmsInt32Number *)data;
    data += sizeof(cmsInt32Number);
    size -= sizeof(cmsInt32Number);

    // Extract cmsFloat64Number from data
    const cmsFloat64Number *params = (const cmsFloat64Number *)data;

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildParametricToneCurve(context, type, params);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}