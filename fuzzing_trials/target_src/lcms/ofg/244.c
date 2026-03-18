#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Initialize a cmsStage object with non-NULL values
    cmsToneCurve *curves[3];
    for (int i = 0; i < 3; i++) {
        curves[i] = cmsBuildGamma(NULL, 2.2);
        if (curves[i] == NULL) {
            for (int j = 0; j < i; j++) {
                cmsFreeToneCurve(curves[j]);
            }
            return 0;
        }
    }

    cmsStage *stage = cmsStageAllocToneCurves(NULL, 3, curves);
    if (stage == NULL) {
        for (int i = 0; i < 3; i++) {
            cmsFreeToneCurve(curves[i]);
        }
        return 0;
    }

    // Call the function-under-test
    cmsStage *dupStage = cmsStageDup(stage);

    // Clean up
    if (dupStage != NULL) {
        cmsStageFree(dupStage);
    }
    cmsStageFree(stage);

    for (int i = 0; i < 3; i++) {
        cmsFreeToneCurve(curves[i]);
    }

    return 0;
}