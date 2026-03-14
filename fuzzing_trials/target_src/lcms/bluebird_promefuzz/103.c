#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static void fuzz_cmsD50_xyY() {
    const cmsCIExyY* d50 = cmsD50_xyY();
    if (d50) {
        // Use d50 in some way if needed
    }
}

static void fuzz_cmsCreateLab4Profile(const cmsCIExyY* whitePoint) {
    cmsHPROFILE profile = cmsCreateLab4Profile(whitePoint);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsCreateGrayProfile(const cmsCIExyY* whitePoint, const cmsToneCurve* transferFunction) {
    cmsHPROFILE profile = cmsCreateGrayProfile(whitePoint, transferFunction);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsxyY2XYZ(const cmsCIExyY* source) {
    cmsCIEXYZ dest;
    cmsxyY2XYZ(&dest, source);
}

static void fuzz_cmsCreateLab2ProfileTHR(cmsContext contextID, const cmsCIExyY* whitePoint) {
    cmsHPROFILE profile = cmsCreateLab2ProfileTHR(contextID, whitePoint);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsCreateGrayProfileTHR(cmsContext contextID, const cmsCIExyY* whitePoint, const cmsToneCurve* transferFunction) {
    cmsHPROFILE profile = cmsCreateGrayProfileTHR(contextID, whitePoint, transferFunction);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY)) {
        return 0;
    }

    const cmsCIExyY* whitePoint = (const cmsCIExyY*)Data;
    const cmsToneCurve* transferFunction = NULL;
    cmsContext contextID = NULL;

    if (Size >= sizeof(cmsCIExyY) + sizeof(cmsContext)) {
        contextID = *(cmsContext*)(Data + sizeof(cmsCIExyY));
    }

    fuzz_cmsD50_xyY();
    fuzz_cmsCreateLab4Profile(whitePoint);
    fuzz_cmsCreateGrayProfile(whitePoint, transferFunction);
    fuzz_cmsxyY2XYZ(whitePoint);
    fuzz_cmsCreateLab2ProfileTHR(contextID, whitePoint);
    fuzz_cmsCreateGrayProfileTHR(contextID, whitePoint, transferFunction);

    return 0;
}