// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCIE94DeltaE at cmspcs.c:451:28 in lcms2.h
// cmsCMCdeltaE at cmspcs.c:548:28 in lcms2.h
// cmsDesaturateLab at cmsgmt.c:515:19 in lcms2.h
// cmsGDBCompute at cmssm.c:550:19 in lcms2.h
// cmsGDBCheckPoint at cmssm.c:390:19 in lcms2.h
// cmsGDBAddPoint at cmssm.c:358:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsCIELab GenerateCIELab(const uint8_t *Data, size_t Size, size_t *Offset) {
    cmsCIELab Lab;
    if (*Offset + sizeof(cmsCIELab) <= Size) {
        memcpy(&Lab, Data + *Offset, sizeof(cmsCIELab));
        *Offset += sizeof(cmsCIELab);
    } else {
        Lab.L = 0.0;
        Lab.a = 0.0;
        Lab.b = 0.0;
    }
    return Lab;
}

int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2 + sizeof(cmsFloat64Number) * 2 + sizeof(cmsUInt32Number)) {
        return 0;
    }

    size_t Offset = 0;
    cmsCIELab Lab1 = GenerateCIELab(Data, Size, &Offset);
    cmsCIELab Lab2 = GenerateCIELab(Data, Size, &Offset);

    cmsFloat64Number l = 0.0, c = 0.0;
    if (Offset + sizeof(cmsFloat64Number) * 2 <= Size) {
        memcpy(&l, Data + Offset, sizeof(cmsFloat64Number));
        Offset += sizeof(cmsFloat64Number);
        memcpy(&c, Data + Offset, sizeof(cmsFloat64Number));
        Offset += sizeof(cmsFloat64Number);
    }

    cmsUInt32Number dwFlags = 0;
    if (Size > Offset + sizeof(cmsUInt32Number)) {
        memcpy(&dwFlags, Data + Offset, sizeof(cmsUInt32Number));
        Offset += sizeof(cmsUInt32Number);
    }

    // Fuzz cmsCIE94DeltaE
    cmsCIE94DeltaE(&Lab1, &Lab2);

    // Fuzz cmsCMCdeltaE
    cmsCMCdeltaE(&Lab1, &Lab2, l, c);

    // Fuzz cmsDesaturateLab
    cmsDesaturateLab(&Lab1, 100.0, -100.0, 100.0, -100.0);

    // Create a dummy GBD handle for testing
    cmsHANDLE hGDB = NULL; // Assume a valid handle is obtained from some initialization function

    // Ensure hGDB is a valid handle before calling cmsGDBCompute
    if (hGDB != NULL) {
        cmsGDBCompute(hGDB, dwFlags);

        // Fuzz cmsGDBCheckPoint
        cmsGDBCheckPoint(hGDB, &Lab1);

        // Fuzz cmsGDBAddPoint
        cmsGDBAddPoint(hGDB, &Lab2);

        // Clean up the GBD handle
        // Assume a valid cleanup function is available
    }

    return 0;
}