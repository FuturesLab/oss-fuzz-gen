#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsToneCurve *curve1 = NULL;
    cmsToneCurve *curve2 = NULL;
    cmsUInt32Number nPoints = 2; // A simple choice for the number of points

    if (size < sizeof(cmsFloat32Number) * nPoints * 2) {
        return 0; // Not enough data to create two tone curves
    }

    // Create two tone curves from the input data
    curve1 = cmsBuildTabulatedToneCurveFloat(context, nPoints, (const cmsFloat32Number *)data);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsBuildTabulatedToneCurveFloat

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsBuildTabulatedToneCurveFloat to cmsCreateGrayProfile
    const cmsCIExyY adcfqhnd;
    memset(&adcfqhnd, 0, sizeof(adcfqhnd));

    cmsHPROFILE ret_cmsCreateGrayProfile_sceqt = cmsCreateGrayProfile(&adcfqhnd, curve1);

    // End mutation: Producer.APPEND_MUTATOR

    curve2 = cmsBuildTabulatedToneCurveFloat(context, LCMS_USED_AS_INPUT, (const cmsFloat32Number *)(data + sizeof(cmsFloat32Number) * nPoints));
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (curve1 != NULL && curve2 != NULL) {
        // Call the function under test
        cmsToneCurve *resultCurve = cmsJoinToneCurve(context, curve1, curve2, nPoints);

        // Clean up the result curve if it was created
        if (resultCurve != NULL) {
            cmsFreeToneCurve(resultCurve);
        }
    }

    // Clean up the tone curves
    if (curve1 != NULL) {
        cmsFreeToneCurve(curve1);
    }
    if (curve2 != NULL) {
        cmsFreeToneCurve(curve2);
    }

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}