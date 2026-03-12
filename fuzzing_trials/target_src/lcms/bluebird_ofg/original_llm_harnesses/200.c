#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    cmsToneCurve *toneCurve = NULL;
    cmsFloat32Number inputValue = 0.5f;  // Initialize with a non-zero value

    // Check if the size is sufficient to create a tone curve
    if (size >= sizeof(cmsUInt16Number)) {
        // Create a tone curve using the data provided
        cmsUInt16Number curvePoints = *(cmsUInt16Number *)data;
        toneCurve = cmsBuildGamma(NULL, curvePoints);

        if (toneCurve != NULL) {
            // Use the rest of the data to determine the input value
            if (size >= sizeof(cmsUInt16Number) + sizeof(cmsFloat32Number)) {
                inputValue = *(cmsFloat32Number *)(data + sizeof(cmsUInt16Number));
            }

            // Call the function-under-test
            cmsFloat32Number result = cmsEvalToneCurveFloat(toneCurve, inputValue);

            // Clean up the tone curve
            cmsFreeToneCurve(toneCurve);
        }
    }

    return 0;
}