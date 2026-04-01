#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsUInt32Number nPoints = 2; // Minimum number of points for a tone curve
    cmsToneCurve *originalCurve = NULL;
    cmsToneCurve *reversedCurve = NULL;
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Ensure data is large enough to create a tone curve
    if (size < sizeof(cmsFloat32Number) * nPoints) {
        return 0;
    }

    // Create a tone curve using the input data
    originalCurve = cmsBuildTabulatedToneCurveFloat(contextID, nPoints, (const cmsFloat32Number *)data);

    // Check if the tone curve was created successfully
    if (originalCurve == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Call the function-under-test
    reversedCurve = cmsReverseToneCurveEx(nPoints, originalCurve);

    // Clean up
    if (reversedCurve != NULL) {
        cmsFreeToneCurve(reversedCurve);
    }
    cmsFreeToneCurve(originalCurve);
    cmsDeleteContext(contextID);

    return 0;
}