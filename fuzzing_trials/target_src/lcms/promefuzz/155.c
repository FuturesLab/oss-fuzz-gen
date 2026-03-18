// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsEvalToneCurve16 at cmsgamma.c:1437:27 in lcms2.h
// cmsGetToneCurveEstimatedTable at cmsgamma.c:774:34 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

static cmsToneCurve* create_random_tone_curve(cmsContext ContextID, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;

    cmsUInt32Number nEntries = *(cmsUInt32Number*)Data;
    Data += sizeof(cmsUInt32Number);
    Size -= sizeof(cmsUInt32Number);

    if (Size < nEntries * sizeof(cmsUInt16Number)) return NULL;

    cmsUInt16Number* values = (cmsUInt16Number*)malloc(nEntries * sizeof(cmsUInt16Number));
    if (!values) return NULL;

    for (cmsUInt32Number i = 0; i < nEntries; i++) {
        values[i] = *(cmsUInt16Number*)Data;
        Data += sizeof(cmsUInt16Number);
    }

    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(ContextID, nEntries, values);
    free(values);
    return curve;
}

int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size) {
    cmsContext ContextID = NULL; // Using default context

    // Create a random tone curve
    cmsToneCurve* curve = create_random_tone_curve(ContextID, Data, Size);
    if (!curve) return 0;

    // Duplicate the tone curve
    cmsToneCurve* dupCurve = cmsDupToneCurve(curve);
    if (dupCurve) {
        cmsFreeToneCurveTriple((cmsToneCurve*[]){dupCurve, NULL, NULL});
    }

    // Evaluate tone curve
    if (Size >= sizeof(cmsUInt16Number)) {
        cmsUInt16Number inputValue = *(cmsUInt16Number*)Data;
        cmsEvalToneCurve16(curve, inputValue);
    }

    // Get estimated table
    const cmsUInt16Number* table = cmsGetToneCurveEstimatedTable(curve);
    if (table) {
        // Just accessing it to ensure it's not NULL
        (void)table;
    }

    // Reverse tone curve
    cmsToneCurve* reverseCurve = cmsReverseToneCurve(curve);
    if (reverseCurve) {
        cmsFreeToneCurveTriple((cmsToneCurve*[]){reverseCurve, NULL, NULL});
    }

    // Free original tone curve
    cmsFreeToneCurveTriple((cmsToneCurve*[]){curve, NULL, NULL});

    return 0;
}