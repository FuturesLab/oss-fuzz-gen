#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nCurves = 2; // Example number of curves

    // Allocate memory for tone curves
    cmsToneCurve **toneCurves = (cmsToneCurve **)malloc(nCurves * sizeof(cmsToneCurve *));
    if (toneCurves == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Initialize tone curves with some values
    for (cmsUInt32Number i = 0; i < nCurves; i++) {
        cmsFloat32Number samplePoints[] = {0.0, 0.5, 1.0};
        toneCurves[i] = cmsBuildTabulatedToneCurveFloat(context, 3, samplePoints);
        if (toneCurves[i] == NULL) {
            for (cmsUInt32Number j = 0; j < i; j++) {
                cmsFreeToneCurve(toneCurves[j]);
            }
            free(toneCurves);
            cmsDeleteContext(context);
            return 0;
        }
    }

    // Call the function-under-test
    cmsStage *stage = cmsStageAllocToneCurves(context, nCurves, (const cmsToneCurve **)toneCurves);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    for (cmsUInt32Number i = 0; i < nCurves; i++) {
        cmsFreeToneCurve(toneCurves[i]);
    }
    free(toneCurves);
    cmsDeleteContext(context);

    return 0;
}