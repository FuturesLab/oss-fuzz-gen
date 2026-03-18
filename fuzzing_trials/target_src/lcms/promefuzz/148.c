// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsD50_xyY at cmswtpnt.c:38:28 in lcms2.h
// cmsAdaptToIlluminant at cmswtpnt.c:328:19 in lcms2.h
// cmsCreateLab4Profile at cmsvirt.c:570:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsLab2XYZ at cmspcs.c:161:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsD50_XYZ at cmswtpnt.c:31:28 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static void fuzz_cmsD50_xyY() {
    const cmsCIExyY* d50_xyY = cmsD50_xyY();
    if (d50_xyY) {
        // Access the D50 xyY values, if needed
    }
}

static void fuzz_cmsAdaptToIlluminant(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) * 3) return;

    cmsCIEXYZ* result = (cmsCIEXYZ*)malloc(sizeof(cmsCIEXYZ));
    const cmsCIEXYZ* sourceWhitePt = (const cmsCIEXYZ*)Data;
    const cmsCIEXYZ* illuminant = (const cmsCIEXYZ*)(Data + sizeof(cmsCIEXYZ));
    const cmsCIEXYZ* value = (const cmsCIEXYZ*)(Data + 2 * sizeof(cmsCIEXYZ));

    if (cmsAdaptToIlluminant(result, sourceWhitePt, illuminant, value)) {
        // Adaptation succeeded, use the result
    }

    free(result);
}

static void fuzz_cmsCreateLab4Profile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) return;

    const cmsCIExyY* whitePoint = (const cmsCIExyY*)Data;
    cmsHPROFILE profile = cmsCreateLab4Profile(whitePoint);
    if (profile) {
        // Profile creation succeeded, use the profile
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsLab2XYZ(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) + sizeof(cmsCIELab)) return;

    const cmsCIEXYZ* whitePoint = (const cmsCIEXYZ*)Data;
    cmsCIEXYZ xyz;
    const cmsCIELab* lab = (const cmsCIELab*)(Data + sizeof(cmsCIEXYZ));

    cmsLab2XYZ(whitePoint, &xyz, lab);
    // Use the converted xyz values
}

static void fuzz_cmsxyY2XYZ(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) return;

    cmsCIEXYZ dest;
    const cmsCIExyY* source = (const cmsCIExyY*)Data;

    cmsxyY2XYZ(&dest, source);
    // Use the converted dest values
}

static void fuzz_cmsD50_XYZ() {
    const cmsCIEXYZ* d50_XYZ = cmsD50_XYZ();
    if (d50_XYZ) {
        // Access the D50 XYZ values, if needed
    }
}

int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size) {
    fuzz_cmsD50_xyY();
    fuzz_cmsAdaptToIlluminant(Data, Size);
    fuzz_cmsCreateLab4Profile(Data, Size);
    fuzz_cmsLab2XYZ(Data, Size);
    fuzz_cmsxyY2XYZ(Data, Size);
    fuzz_cmsD50_XYZ();
    return 0;
}