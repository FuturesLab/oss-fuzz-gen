#include <stdint.h>
#include <lcms2.h>
#include <string.h> // Include for memcpy

extern int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 3 + sizeof(cmsCurveSegment)) {
        return 0; // Not enough data to construct a segment
    }

    // Initialize variables for the function call
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nSegments = 1; // Use a simple case with one segment

    // Define a simple cmsCurveSegment
    cmsCurveSegment segment;
    segment.Type = 1; // Assume a simple type for demonstration

    // Copy data into segment parameters
    memcpy(segment.Params, data, sizeof(double) * 3);
    segment.x0 = 0.0; // Starting point of the segment
    segment.x1 = 1.0; // Ending point of the segment
    segment.nGridPoints = 0; // Not used for Type != 0
    segment.SampledPoints = NULL; // Not used for Type != 0

    // Call the function-under-test
    cmsToneCurve *toneCurve = cmsBuildSegmentedToneCurve(context, nSegments, &segment);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}