#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_450(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsFloat64Number gammaValue;
    cmsToneCurve *toneCurve = NULL;

    if (size < sizeof(cmsFloat64Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Ensure the data is used to form a valid cmsFloat64Number
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