#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <lcms2.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the fuzzing process
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a tone curve with a predefined number of segments
    int nSegments = 5;
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(context, nSegments, NULL);
    if (toneCurve == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Extract a cmsFloat64Number from the input data
    cmsFloat64Number smoothness = *((cmsFloat64Number *)data);

    // Call the function-under-test
    cmsBool result = cmsSmoothToneCurve(toneCurve, smoothness);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}