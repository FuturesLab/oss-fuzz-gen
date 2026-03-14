#include <stdint.h>
#include <lcms2.h>

// Fuzzing harness for cmsIsToneCurveMonotonic
int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a valid tone curve
    if (size < 2) {
        return 0; // Not enough data to form a valid cmsToneCurve
    }

    // Create a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Calculate the number of nodes we can create
    size_t numNodes = size / sizeof(uint16_t);

    // Allocate memory for cmsToneCurve
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(context, numNodes, (const uint16_t *)data);

    if (toneCurve == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function under test
    cmsBool isMonotonic = cmsIsToneCurveMonotonic(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}