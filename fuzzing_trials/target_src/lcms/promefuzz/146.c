// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildSegmentedToneCurve at cmsgamma.c:797:25 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsBuildTabulatedToneCurveFloat at cmsgamma.c:832:25 in lcms2.h
// cmsJoinToneCurve at cmsgamma.c:980:25 in lcms2.h
// cmsReverseToneCurveEx at cmsgamma.c:1070:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lcms2.h>

static cmsContext createContext() {
    return cmsCreateContext(NULL, NULL);
}

static cmsCurveSegment* createCurveSegments(size_t nSegments) {
    cmsCurveSegment* segments = (cmsCurveSegment*)malloc(nSegments * sizeof(cmsCurveSegment));
    if (!segments) return NULL;
    // Initialize segments with dummy data
    for (size_t i = 0; i < nSegments; i++) {
        segments[i].Type = 0; // Example type
        segments[i].Params[0] = 1.0; // Example parameter
    }
    return segments;
}

static cmsToneCurve* buildSegmentedToneCurve(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;
    cmsUInt32Number nSegments = *(cmsUInt32Number*)Data;
    cmsCurveSegment* segments = createCurveSegments(nSegments);
    if (!segments) return NULL;
    cmsToneCurve* curve = cmsBuildSegmentedToneCurve(context, nSegments, segments);
    free(segments);
    return curve;
}

static cmsToneCurve* buildTabulatedToneCurve16(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;
    cmsUInt32Number nEntries = *(cmsUInt32Number*)Data;
    if (Size < sizeof(cmsUInt32Number) + nEntries * sizeof(cmsUInt16Number)) return NULL;
    const cmsUInt16Number* values = (const cmsUInt16Number*)(Data + sizeof(cmsUInt32Number));
    return cmsBuildTabulatedToneCurve16(context, nEntries, values);
}

static cmsToneCurve* buildTabulatedToneCurveFloat(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;
    cmsUInt32Number nEntries = *(cmsUInt32Number*)Data;
    if (Size < sizeof(cmsUInt32Number) + nEntries * sizeof(cmsFloat32Number)) return NULL;
    const cmsFloat32Number* values = (const cmsFloat32Number*)(Data + sizeof(cmsUInt32Number));
    return cmsBuildTabulatedToneCurveFloat(context, nEntries, values);
}

static cmsToneCurve* joinToneCurve(cmsContext context, cmsToneCurve* X, cmsToneCurve* Y, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;
    cmsUInt32Number nPoints = *(cmsUInt32Number*)Data;
    return cmsJoinToneCurve(context, X, Y, nPoints);
}

static cmsToneCurve* reverseToneCurveEx(cmsUInt32Number nResultSamples, cmsToneCurve* InGamma) {
    return cmsReverseToneCurveEx(nResultSamples, InGamma);
}

static void fuzzToneCurves(cmsContext context, const uint8_t *Data, size_t Size) {
    cmsToneCurve* curve1 = buildSegmentedToneCurve(context, Data, Size);
    cmsToneCurve* curve2 = buildTabulatedToneCurve16(context, Data, Size);
    cmsToneCurve* curve3 = buildTabulatedToneCurveFloat(context, Data, Size);

    if (curve1 && curve2) {
        cmsToneCurve* joinedCurve = joinToneCurve(context, curve1, curve2, Data, Size);
        if (joinedCurve) cmsFreeToneCurve(joinedCurve);
    }

    if (curve3) {
        cmsToneCurve* reversedCurve = reverseToneCurveEx(256, curve3);
        if (reversedCurve) cmsFreeToneCurve(reversedCurve);
    }

    if (curve1) cmsFreeToneCurve(curve1);
    if (curve2) cmsFreeToneCurve(curve2);
    if (curve3) cmsFreeToneCurve(curve3);
}

int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    cmsContext context = createContext();
    if (!context) return 0;

    fuzzToneCurves(context, Data, Size);

    cmsDeleteContext(context);
    return 0;
}