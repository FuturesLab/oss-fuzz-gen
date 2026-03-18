// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsSmoothToneCurve at cmsgamma.c:1213:20 in lcms2.h
// cmsGetToneCurveParametricType at cmsgamma.c:1409:27 in lcms2.h
// cmsIsToneCurveMonotonic at cmsgamma.c:1347:20 in lcms2.h
// cmsIsToneCurveLinear at cmsgamma.c:1329:19 in lcms2.h
// cmsIsToneCurveMultisegment at cmsgamma.c:1402:20 in lcms2.h
// cmsIsToneCurveDescending at cmsgamma.c:1393:20 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
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

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
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