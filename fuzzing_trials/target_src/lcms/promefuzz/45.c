// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurveFloat at cmsgamma.c:832:25 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsEvalToneCurveFloat at cmsgamma.c:1418:28 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsReverseToneCurveEx at cmsgamma.c:1070:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static cmsToneCurve* create_sample_tone_curve(cmsContext ContextID) {
    cmsFloat32Number sampleValues[3] = {0.0f, 0.5f, 1.0f};
    return cmsBuildTabulatedToneCurveFloat(ContextID, 3, sampleValues);
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat32Number)) return 0;

    cmsContext context = NULL;
    cmsToneCurve* toneCurve = create_sample_tone_curve(context);
    if (!toneCurve) return 0;

    cmsToneCurve* dupCurve = cmsDupToneCurve(toneCurve);
    if (dupCurve) {
        cmsEvalToneCurveFloat(dupCurve, *((cmsFloat32Number*)Data));
        cmsFreeToneCurveTriple((cmsToneCurve*[]){dupCurve, NULL, NULL});
    }

    cmsToneCurve* reverseCurveEx = cmsReverseToneCurveEx(256, toneCurve);
    if (reverseCurveEx) {
        cmsFreeToneCurveTriple((cmsToneCurve*[]){reverseCurveEx, NULL, NULL});
    }

    cmsToneCurve* reverseCurve = cmsReverseToneCurve(toneCurve);
    if (reverseCurve) {
        cmsFreeToneCurveTriple((cmsToneCurve*[]){reverseCurve, NULL, NULL});
    }

    cmsFreeToneCurveTriple((cmsToneCurve*[]){toneCurve, NULL, NULL});
    return 0;
}