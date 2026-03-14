#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

static void fuzz_cmsCIECAM02Reverse(cmsHANDLE hModel, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsJCh)) {
        return;
    }

    cmsJCh* pIn = (cmsJCh*)Data;
    cmsCIEXYZ pOut;
    cmsCIECAM02Reverse(hModel, pIn, &pOut);
}

static void fuzz_cmsCIECAM02Done(cmsHANDLE hModel) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCIECAM02Done with cmsGBDFree
    cmsGBDFree(hModel);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


}

static void fuzz_cmsCIE2000DeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab) + 3 * sizeof(cmsFloat64Number)) {
        return;
    }

    const cmsCIELab* Lab1 = (const cmsCIELab*)Data;
    const cmsCIELab* Lab2 = (const cmsCIELab*)(Data + sizeof(cmsCIELab));
    cmsFloat64Number Kl = *((cmsFloat64Number*)(Data + 2 * sizeof(cmsCIELab)));
    cmsFloat64Number Kc = *((cmsFloat64Number*)(Data + 2 * sizeof(cmsCIELab) + sizeof(cmsFloat64Number)));
    cmsFloat64Number Kh = *((cmsFloat64Number*)(Data + 2 * sizeof(cmsCIELab) + 2 * sizeof(cmsFloat64Number)));

    cmsCIE2000DeltaE(Lab1, Lab2, Kl, Kc, Kh);
}

static void fuzz_cmsLab2LCh(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab)) {
        return;
    }

    cmsCIELCh LCh;
    const cmsCIELab* Lab = (const cmsCIELab*)Data;
    cmsLab2LCh(&LCh, Lab);
}

static void fuzz_cmsCIECAM02Forward(cmsHANDLE hModel, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ)) {
        return;
    }

    const cmsCIEXYZ* pIn = (const cmsCIEXYZ*)Data;
    cmsJCh pOut;
    cmsCIECAM02Forward(hModel, pIn, &pOut);
}

static void fuzz_cmsCIECAM02Init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsViewingConditions)) {
        return;
    }

    cmsContext ContextID = NULL; // Assuming default context
    const cmsViewingConditions* pVC = (const cmsViewingConditions*)Data;
    cmsHANDLE hModel = cmsCIECAM02Init(ContextID, pVC);

    if (hModel) {
        fuzz_cmsCIECAM02Reverse(hModel, Data, Size);
        fuzz_cmsCIECAM02Forward(hModel, Data, Size);
        fuzz_cmsCIECAM02Done(hModel);
    }
}

int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    fuzz_cmsCIE2000DeltaE(Data, Size);
    fuzz_cmsLab2LCh(Data, Size);
    fuzz_cmsCIECAM02Init(Data, Size);
    return 0;
}