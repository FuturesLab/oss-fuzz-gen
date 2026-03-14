// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsCreateXYZProfileTHR at cmsvirt.c:577:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateLab2ProfileTHR at cmsvirt.c:473:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateGrayProfileTHR at cmsvirt.c:227:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsCreate_OkLabProfile at cmsvirt.c:690:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsContext createDummyContext() {
    return cmsCreateContext(NULL, NULL);
}

static cmsCIExyY* createDummyWhitePoint() {
    cmsCIExyY* whitePoint = (cmsCIExyY*)malloc(sizeof(cmsCIExyY));
    if (whitePoint) {
        whitePoint->x = 0.3127;
        whitePoint->y = 0.3290;
        whitePoint->Y = 1.0;
    }
    return whitePoint;
}

static cmsCIExyYTRIPLE* createDummyPrimaries() {
    cmsCIExyYTRIPLE* primaries = (cmsCIExyYTRIPLE*)malloc(sizeof(cmsCIExyYTRIPLE));
    if (primaries) {
        primaries->Red.x = 0.64;
        primaries->Red.y = 0.33;
        primaries->Red.Y = 1.0;
        primaries->Green.x = 0.30;
        primaries->Green.y = 0.60;
        primaries->Green.Y = 1.0;
        primaries->Blue.x = 0.15;
        primaries->Blue.y = 0.06;
        primaries->Blue.Y = 1.0;
    }
    return primaries;
}

static cmsToneCurve* createDummyToneCurve() {
    return cmsBuildGamma(NULL, 2.2);
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    cmsContext context = createDummyContext();
    if (!context) return 0;

    cmsHPROFILE profile = cmsCreateXYZProfileTHR(context);
    if (profile) cmsCloseProfile(profile);

    cmsContext dupContext = cmsDupContext(context, NULL);
    if (dupContext) cmsDeleteContext(dupContext);

    cmsCIExyY* whitePoint = createDummyWhitePoint();
    if (whitePoint) {
        profile = cmsCreateLab2ProfileTHR(context, whitePoint);
        if (profile) cmsCloseProfile(profile);

        cmsToneCurve* toneCurve = createDummyToneCurve();
        if (toneCurve) {
            cmsCIExyYTRIPLE* primaries = createDummyPrimaries();
            if (primaries) {
                profile = cmsCreateRGBProfileTHR(context, whitePoint, primaries, (cmsToneCurve* const[3]){toneCurve, toneCurve, toneCurve});
                if (profile) cmsCloseProfile(profile);
                free(primaries);
            }

            profile = cmsCreateGrayProfileTHR(context, whitePoint, toneCurve);
            if (profile) cmsCloseProfile(profile);

            cmsFreeToneCurve(toneCurve);
        }
        free(whitePoint);
    }

    profile = cmsCreate_OkLabProfile(context);
    if (profile) cmsCloseProfile(profile);

    cmsDeleteContext(context);

    return 0;
}