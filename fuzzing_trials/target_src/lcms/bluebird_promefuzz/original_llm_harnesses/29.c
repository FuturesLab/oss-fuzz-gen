// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsSmoothToneCurve at cmsgamma.c:1213:20 in lcms2.h
// cmsEstimateGamma at cmsgamma.c:1465:28 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsBuildParametricToneCurve at cmsgamma.c:880:25 in lcms2.h
// cmsIsToneCurveLinear at cmsgamma.c:1329:19 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsDetectRGBProfileGamma at cmsgmt.c:605:28 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static void fuzz_cmsSmoothToneCurve(cmsToneCurve* curve, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) return;
    cmsFloat64Number lambda;
    memcpy(&lambda, Data, sizeof(cmsFloat64Number));
    cmsSmoothToneCurve(curve, lambda);
}

static void fuzz_cmsEstimateGamma(const cmsToneCurve* curve, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) return;
    cmsFloat64Number precision;
    memcpy(&precision, Data, sizeof(cmsFloat64Number));
    cmsEstimateGamma(curve, precision);
}

static cmsToneCurve* fuzz_cmsBuildGamma(cmsContext context, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) return NULL;
    cmsFloat64Number gamma;
    memcpy(&gamma, Data, sizeof(cmsFloat64Number));
    return cmsBuildGamma(context, gamma);
}

static cmsToneCurve* fuzz_cmsBuildParametricToneCurve(cmsContext context, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(cmsInt32Number) + sizeof(cmsFloat64Number)) return NULL;
    cmsInt32Number type;
    memcpy(&type, Data, sizeof(cmsInt32Number));
    cmsFloat64Number params[10];
    size_t numParams = (Size - sizeof(cmsInt32Number)) / sizeof(cmsFloat64Number);
    if (numParams > 10) numParams = 10;
    memcpy(params, Data + sizeof(cmsInt32Number), numParams * sizeof(cmsFloat64Number));
    return cmsBuildParametricToneCurve(context, type, params);
}

static void fuzz_cmsIsToneCurveLinear(const cmsToneCurve* curve) {
    cmsIsToneCurveLinear(curve);
}

static void fuzz_cmsDetectRGBProfileGamma(const uint8_t* Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) return;
    cmsHPROFILE profile = NULL;
    cmsFloat64Number threshold;
    memcpy(&threshold, Data, sizeof(cmsFloat64Number));

    // Use a dummy profile handle if necessary
    profile = cmsOpenProfileFromFile("./dummy_file", "r");
    if (profile) {
        cmsDetectRGBProfileGamma(profile, threshold);
        cmsCloseProfile(profile);
    }
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    cmsContext context = NULL;

    // Fuzz cmsBuildGamma
    cmsToneCurve* gammaCurve = fuzz_cmsBuildGamma(context, Data, Size);
    if (gammaCurve) {
        // Fuzz cmsSmoothToneCurve and cmsEstimateGamma
        fuzz_cmsSmoothToneCurve(gammaCurve, Data, Size);
        fuzz_cmsEstimateGamma(gammaCurve, Data, Size);
        fuzz_cmsIsToneCurveLinear(gammaCurve);
        cmsFreeToneCurve(gammaCurve);
    }

    // Fuzz cmsBuildParametricToneCurve
    cmsToneCurve* parametricCurve = fuzz_cmsBuildParametricToneCurve(context, Data, Size);
    if (parametricCurve) {
        // Fuzz cmsSmoothToneCurve and cmsEstimateGamma
        fuzz_cmsSmoothToneCurve(parametricCurve, Data, Size);
        fuzz_cmsEstimateGamma(parametricCurve, Data, Size);
        fuzz_cmsIsToneCurveLinear(parametricCurve);
        cmsFreeToneCurve(parametricCurve);
    }

    // Fuzz cmsDetectRGBProfileGamma
    fuzz_cmsDetectRGBProfileGamma(Data, Size);

    return 0;
}