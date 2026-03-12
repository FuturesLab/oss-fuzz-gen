#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static cmsToneCurve* CreateToneCurveFromData(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number)) {
        return NULL;
    }

    cmsUInt32Number nEntries = Size / sizeof(cmsUInt16Number);
    cmsUInt16Number* table = (cmsUInt16Number*)malloc(nEntries * sizeof(cmsUInt16Number));
    if (!table) {
        return NULL;
    }

    memcpy(table, Data, nEntries * sizeof(cmsUInt16Number));

    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(NULL, nEntries, table);
    free(table);
    return curve;
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    cmsToneCurve* curve = CreateToneCurveFromData(Data, Size);
    if (!curve) {
        return 0;
    }

    // Fuzz cmsSmoothToneCurve
    cmsSmoothToneCurve(curve, 0.1);

    // Fuzz cmsGetToneCurveParametricType
    cmsGetToneCurveParametricType(curve);

    // Fuzz cmsIsToneCurveMonotonic
    cmsIsToneCurveMonotonic(curve);

    // Fuzz cmsIsToneCurveLinear
    cmsIsToneCurveLinear(curve);

    // Fuzz cmsIsToneCurveMultisegment
    cmsIsToneCurveMultisegment(curve);

    // Fuzz cmsIsToneCurveDescending
    cmsIsToneCurveDescending(curve);

    cmsFreeToneCurve(curve);
    return 0;
}