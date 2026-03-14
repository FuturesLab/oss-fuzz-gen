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

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
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