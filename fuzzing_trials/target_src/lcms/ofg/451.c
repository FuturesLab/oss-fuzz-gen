#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_451(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsFloat64Number gammaValue;
    cmsToneCurve *toneCurve;

    // Initialize the context
    context = cmsCreateContext(NULL, NULL);

    // Ensure the data is large enough to extract a double
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Extract a cmsFloat64Number from the input data
    gammaValue = *((cmsFloat64Number *)data);

    // Call the function-under-test
    toneCurve = cmsBuildGamma(context, gammaValue);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }
    cmsDeleteContext(context);

    return 0;
}