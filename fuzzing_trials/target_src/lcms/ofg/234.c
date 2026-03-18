#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_234(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    cmsUInt32Number nCurves = *((cmsUInt32Number *)data);
    data += sizeof(cmsUInt32Number);
    size -= sizeof(cmsUInt32Number);

    if (nCurves == 0 || size < nCurves * sizeof(cmsToneCurve *)) {
        cmsDeleteContext(context);
        return 0;
    }

    const cmsToneCurve **curves = (const cmsToneCurve **)malloc(nCurves * sizeof(cmsToneCurve *));
    if (curves == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    for (cmsUInt32Number i = 0; i < nCurves; i++) {
        curves[i] = cmsBuildGamma(context, 2.2);  // Example: create a simple gamma curve
        if (curves[i] == NULL) {
            for (cmsUInt32Number j = 0; j < i; j++) {
                cmsFreeToneCurve(curves[j]);
            }
            free(curves);
            cmsDeleteContext(context);
            return 0;
        }
    }

    cmsStage *stage = cmsStageAllocToneCurves(context, nCurves, curves);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    for (cmsUInt32Number i = 0; i < nCurves; i++) {
        cmsFreeToneCurve((cmsToneCurve *)curves[i]);
    }
    free(curves);
    cmsDeleteContext(context);

    return 0;
}