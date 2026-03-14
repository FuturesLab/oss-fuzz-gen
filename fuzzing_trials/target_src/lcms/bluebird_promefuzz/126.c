#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static void initializeToneCurveTriple(cmsToneCurve* Curve[3]) {
    for (int i = 0; i < 3; i++) {
        Curve[i] = cmsBuildGamma(NULL, 2.2); // Example gamma curve
    }
}

static cmsToneCurve* createToneCurveFromData(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + sizeof(cmsUInt16Number)) {
        return NULL;
    }
    cmsUInt32Number nEntries = *((cmsUInt32Number*)Data);
    nEntries = nEntries % 4096 + 1; // Limit entries to a reasonable size

    size_t requiredSize = sizeof(cmsUInt32Number) + nEntries * sizeof(cmsUInt16Number);
    if (Size < requiredSize) {
        return NULL;
    }

    return cmsBuildTabulatedToneCurve16(NULL, nEntries, (const cmsUInt16Number*)(Data + sizeof(cmsUInt32Number)));
}

int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + sizeof(cmsUInt16Number)) {
        return 0;
    }

    cmsToneCurve* triple[3];
    initializeToneCurveTriple(triple);

    cmsFreeToneCurveTriple(triple);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsFreeToneCurveTriple to cmsOpenProfileFromMemTHR
    cmsContext ret_cmsGetProfileContextID_aaiyr = cmsGetProfileContextID(0);

    cmsHPROFILE ret_cmsOpenProfileFromMemTHR_zcwwx = cmsOpenProfileFromMemTHR(ret_cmsGetProfileContextID_aaiyr, (const void *)*triple, D_CALCULATE);

    // End mutation: Producer.APPEND_MUTATOR

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


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsFreeToneCurveTriple to cmsCreateContext
            char owtblvdi[1024] = "xovwh";

            cmsContext ret_cmsCreateContext_khgch = cmsCreateContext(owtblvdi, (void *)*triple);

            // End mutation: Producer.APPEND_MUTATOR

        cmsFreeToneCurveTriple((cmsToneCurve*[]){original, NULL, NULL});
    }    return 0;
}