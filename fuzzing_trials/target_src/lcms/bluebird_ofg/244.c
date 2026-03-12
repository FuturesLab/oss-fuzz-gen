#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsToneCurve *curve1 = NULL;
    cmsToneCurve *curve2 = NULL;
    cmsUInt32Number location = 0;

    // Ensure the size is sufficient to create tone curves
    if (size < 2 * sizeof(cmsUInt16Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Calculate number of points for the tone curves
    cmsUInt32Number nPoints = size / sizeof(cmsUInt16Number);

    // Ensure there are enough points to form a valid tone curve
    if (nPoints < 2) {
        cmsDeleteContext(context);
        return 0;
    }

    // Create tone curves from the input data
    curve1 = cmsBuildTabulatedToneCurve16(context, nPoints, (const cmsUInt16Number *)data);
    curve2 = cmsBuildTabulatedToneCurve16(context, nPoints, (const cmsUInt16Number *)data);

    // Check if the tone curves were successfully created
    if (curve1 == NULL || curve2 == NULL) {
        if (curve1) cmsFreeToneCurve(curve1);
        if (curve2) cmsFreeToneCurve(curve2);
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsToneCurve *resultCurve = cmsJoinToneCurve(context, curve1, curve2, location);

    // Clean up
    if (curve1) cmsFreeToneCurve(curve1);
    if (curve2) cmsFreeToneCurve(curve2);
    if (resultCurve) cmsFreeToneCurve(resultCurve);
    cmsDeleteContext(context);

    return 0;
}