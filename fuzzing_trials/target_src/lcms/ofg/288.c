#include <stdint.h>
#include <lcms2.h>

// Fuzzing harness for cmsGetToneCurveParametricType
int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Check if the input size is sufficient to extract a gamma value
    if (size < sizeof(double)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Extract a gamma value from the input data
    double gamma;
    memcpy(&gamma, data, sizeof(double));

    // Create a tone curve with a gamma value based on the input data
    cmsToneCurve *toneCurve = cmsBuildGamma(context, gamma);
    if (toneCurve == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsInt32Number parametricType = cmsGetToneCurveParametricType(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}