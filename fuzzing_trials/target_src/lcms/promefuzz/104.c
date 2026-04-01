// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsXYZ2xyY at cmspcs.c:91:16 in lcms2.h
// cmsD50_xyY at cmswtpnt.c:38:28 in lcms2.h
// cmsCreateLab4Profile at cmsvirt.c:570:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsXYZ2Lab at cmspcs.c:143:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsTempFromWhitePoint at cmswtpnt.c:143:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcms2.h"

static void fuzz_cmsXYZ2xyY(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ)) return;

    cmsCIExyY Dest;
    cmsCIEXYZ Source;
    memcpy(&Source, Data, sizeof(cmsCIEXYZ));

    cmsXYZ2xyY(&Dest, &Source);
}

static void fuzz_cmsD50_xyY() {
    const cmsCIExyY* D50xyY = cmsD50_xyY();
    (void)D50xyY; // Use the value to avoid unused variable warning
}

static void fuzz_cmsCreateLab4Profile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) return;

    cmsCIExyY WhitePoint;
    memcpy(&WhitePoint, Data, sizeof(cmsCIExyY));

    cmsHPROFILE profile = cmsCreateLab4Profile(&WhitePoint);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsXYZ2Lab(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) * 2) return;

    cmsCIEXYZ WhitePoint, xyz;
    cmsCIELab Lab;
    memcpy(&WhitePoint, Data, sizeof(cmsCIEXYZ));
    memcpy(&xyz, Data + sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));

    cmsXYZ2Lab(&WhitePoint, &Lab, &xyz);
}

static void fuzz_cmsxyY2XYZ(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) return;

    cmsCIEXYZ Dest;
    cmsCIExyY Source;
    memcpy(&Source, Data, sizeof(cmsCIExyY));

    cmsxyY2XYZ(&Dest, &Source);
}

static void fuzz_cmsTempFromWhitePoint(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) return;

    cmsCIExyY WhitePoint;
    cmsFloat64Number TempK;
    memcpy(&WhitePoint, Data, sizeof(cmsCIExyY));

    cmsBool result = cmsTempFromWhitePoint(&TempK, &WhitePoint);
    (void)result; // Use the value to avoid unused variable warning
}

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    fuzz_cmsXYZ2xyY(Data, Size);
    fuzz_cmsD50_xyY();
    fuzz_cmsCreateLab4Profile(Data, Size);
    fuzz_cmsXYZ2Lab(Data, Size);
    fuzz_cmsxyY2XYZ(Data, Size);
    fuzz_cmsTempFromWhitePoint(Data, Size);

    return 0;
}