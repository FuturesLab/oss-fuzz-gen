#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(uint16_t) * 256) {
        return 0;
    }

    // Create a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Allocate memory for cmsToneCurve
    cmsToneCurve *toneCurve = cmsBuildTabulatedToneCurve16(context, 256, (const uint16_t*)data);

    // Check if the tone curve is monotonic
    if (toneCurve != NULL) {
        cmsBool result = cmsIsToneCurveMonotonic(toneCurve);
        (void)result; // To avoid unused variable warning
    }

    // Free the tone curve
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    // Delete the context
    cmsDeleteContext(context);

    return 0;
}

#ifdef __cplusplus
}
#endif