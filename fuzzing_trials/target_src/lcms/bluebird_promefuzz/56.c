#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcms2.h"

static void fuzz_cmsDeltaE(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2) return;

    const cmsCIELab *Lab1 = (const cmsCIELab *)Data;
    const cmsCIELab *Lab2 = (const cmsCIELab *)(Data + sizeof(cmsCIELab));

    cmsFloat64Number deltaE = cmsDeltaE(Lab1, Lab2);
    (void)deltaE; // Suppress unused variable warning
}

static void fuzz_cmsBFDdeltaE(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2) return;

    const cmsCIELab *Lab1 = (const cmsCIELab *)Data;
    const cmsCIELab *Lab2 = (const cmsCIELab *)(Data + sizeof(cmsCIELab));

    cmsFloat64Number bfdDeltaE = cmsBFDdeltaE(Lab1, Lab2);
    (void)bfdDeltaE; // Suppress unused variable warning
}

static void fuzz_cmsLabEncoded2FloatV2(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * 3) return;

    cmsCIELab Lab;
    const cmsUInt16Number *wLab = (const cmsUInt16Number *)Data;

    cmsLabEncoded2FloatV2(&Lab, wLab);
}

static void fuzz_cmsLabEncoded2Float(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * 3) return;

    cmsCIELab Lab;
    const cmsUInt16Number *wLab = (const cmsUInt16Number *)Data;

    cmsLabEncoded2Float(&Lab, wLab);
}

static void fuzz_cmsFloat2LabEncodedV2(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab)) return;

    cmsUInt16Number wLab[3];
    const cmsCIELab *Lab = (const cmsCIELab *)Data;

    cmsFloat2LabEncodedV2(wLab, Lab);
}

static void fuzz_cmsFloat2LabEncoded(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab)) return;

    cmsUInt16Number wLab[3];
    const cmsCIELab *Lab = (const cmsCIELab *)Data;

    cmsFloat2LabEncoded(wLab, Lab);
}

int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    fuzz_cmsDeltaE(Data, Size);
    fuzz_cmsBFDdeltaE(Data, Size);
    fuzz_cmsLabEncoded2FloatV2(Data, Size);
    fuzz_cmsLabEncoded2Float(Data, Size);
    fuzz_cmsFloat2LabEncodedV2(Data, Size);
    fuzz_cmsFloat2LabEncoded(Data, Size);

    return 0;
}