#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "lcms2.h"

static void fuzz_cmsCIE94DeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab)) return;

    cmsCIELab Lab1, Lab2;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));

    cmsFloat64Number deltaE = cmsCIE94DeltaE(&Lab1, &Lab2);
}

static void fuzz_cmsCMCdeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab) + 2 * sizeof(cmsFloat64Number)) return;

    cmsCIELab Lab1, Lab2;
    cmsFloat64Number l, c;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));
    memcpy(&l, Data + 2 * sizeof(cmsCIELab), sizeof(cmsFloat64Number));
    memcpy(&c, Data + 2 * sizeof(cmsCIELab) + sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));

    cmsFloat64Number deltaE = cmsCMCdeltaE(&Lab1, &Lab2, l, c);
}

static void fuzz_cmsDeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab)) return;

    cmsCIELab Lab1, Lab2;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));

    cmsFloat64Number deltaE = cmsDeltaE(&Lab1, &Lab2);
}

static void fuzz_cmsBFDdeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab)) return;

    cmsCIELab Lab1, Lab2;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));

    cmsFloat64Number deltaE = cmsBFDdeltaE(&Lab1, &Lab2);
}

static void fuzz_cmsDesaturateLab(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) + 4 * sizeof(double)) return;

    cmsCIELab Lab;
    double amax, amin, bmax, bmin;
    memcpy(&Lab, Data, sizeof(cmsCIELab));
    memcpy(&amax, Data + sizeof(cmsCIELab), sizeof(double));
    memcpy(&amin, Data + sizeof(cmsCIELab) + sizeof(double), sizeof(double));
    memcpy(&bmax, Data + sizeof(cmsCIELab) + 2 * sizeof(double), sizeof(double));
    memcpy(&bmin, Data + sizeof(cmsCIELab) + 3 * sizeof(double), sizeof(double));

    cmsBool result = cmsDesaturateLab(&Lab, amax, amin, bmax, bmin);
}

static void fuzz_cmsCIE2000DeltaE(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsCIELab) + 3 * sizeof(cmsFloat64Number)) return;

    cmsCIELab Lab1, Lab2;
    cmsFloat64Number Kl, Kc, Kh;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));
    memcpy(&Kl, Data + 2 * sizeof(cmsCIELab), sizeof(cmsFloat64Number));
    memcpy(&Kc, Data + 2 * sizeof(cmsCIELab) + sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));
    memcpy(&Kh, Data + 2 * sizeof(cmsCIELab) + 2 * sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));

    cmsFloat64Number deltaE = cmsCIE2000DeltaE(&Lab1, &Lab2, Kl, Kc, Kh);
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    fuzz_cmsCIE94DeltaE(Data, Size);
    fuzz_cmsCMCdeltaE(Data, Size);
    fuzz_cmsDeltaE(Data, Size);
    fuzz_cmsBFDdeltaE(Data, Size);
    fuzz_cmsDesaturateLab(Data, Size);
    fuzz_cmsCIE2000DeltaE(Data, Size);
    return 0;
}