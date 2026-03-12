// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsReverseToneCurveEx at cmsgamma.c:1070:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsGetToneCurveEstimatedTableEntries at cmsgamma.c:768:27 in lcms2.h
// cmsJoinToneCurve at cmsgamma.c:980:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

static void initializeToneCurveTriple(cmsToneCurve* Curve[3]) {
    for (int i = 0; i < 3; i++) {
        Curve[i] = cmsBuildGamma(NULL, 2.2); // Example gamma curve
    }
}

static cmsToneCurve* createToneCurveFromData(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + sizeof(cmsUInt16Number)) return NULL;
    cmsUInt32Number nEntries = *((cmsUInt32Number*)Data);
    nEntries = nEntries % 4096 + 1; // Limit entries to a reasonable size

    size_t requiredSize = sizeof(cmsUInt32Number) + nEntries * sizeof(cmsUInt16Number);
    if (Size < requiredSize) return NULL;

    return cmsBuildTabulatedToneCurve16(NULL, nEntries, (const cmsUInt16Number*)(Data + sizeof(cmsUInt32Number)));
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + sizeof(cmsUInt16Number)) return 0;

    cmsToneCurve* triple[3];
    initializeToneCurveTriple(triple);

    cmsFreeToneCurveTriple(triple);

    cmsToneCurve* original = createToneCurveFromData(Data, Size);
    if (original) {
        cmsToneCurve* duplicate = cmsDupToneCurve(original);
        if (duplicate) {
            cmsFreeToneCurveTriple((cmsToneCurve*[]){duplicate, NULL, NULL});
        }

        cmsToneCurve* reverseEx = cmsReverseToneCurveEx(256, original);
        if (reverseEx) {
            cmsFreeToneCurveTriple((cmsToneCurve*[]){reverseEx, NULL, NULL});
        }

        cmsToneCurve* reverse = cmsReverseToneCurve(original);
        if (reverse) {
            cmsFreeToneCurveTriple((cmsToneCurve*[]){reverse, NULL, NULL});
        }

        cmsUInt32Number entries = cmsGetToneCurveEstimatedTableEntries(original);

        cmsToneCurve* joined = cmsJoinToneCurve(NULL, original, original, entries);
        if (joined) {
            cmsFreeToneCurveTriple((cmsToneCurve*[]){joined, NULL, NULL});
        }

        cmsFreeToneCurveTriple((cmsToneCurve*[]){original, NULL, NULL});
    }

    return 0;
}