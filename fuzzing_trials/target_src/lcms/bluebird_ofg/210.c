#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure that there's enough data to construct a valid segment
    if (size < sizeof(cmsFloat64Number) * 10) {
        return 0; // Not enough data to proceed
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0; // Failed to create context
    }

    cmsUInt32Number nSegments = 1; // Number of segments in the tone curve

    // Define a simple curve segment for testing
    cmsCurveSegment segment;
    segment.x0 = 0.0;
    segment.x1 = 1.0;
    segment.Type = 6; // Use a valid segment type, such as 6 for a parametric curve

    // Initialize parameters for the segment
    memcpy(segment.Params, data, sizeof(cmsFloat64Number) * 10);

    cmsCurveSegment *segments = (cmsCurveSegment *)malloc(sizeof(cmsCurveSegment));
    if (segments == NULL) {
        cmsDeleteContext(context);
        return 0; // Failed to allocate memory
    }
    memcpy(segments, &segment, sizeof(cmsCurveSegment));

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildSegmentedToneCurve(context, nSegments, segments);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    free(segments);
    cmsDeleteContext(context);

    return 0;
}