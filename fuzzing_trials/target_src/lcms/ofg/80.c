#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt16Number)) {
        return 0; // Not enough data to extract a cmsUInt16Number
    }

    // Initialize a cmsToneCurve object
    cmsToneCurve *toneCurve = cmsBuildGamma(NULL, 2.2); // Using a gamma of 2.2 as an example

    // Extract a cmsUInt16Number from the input data
    cmsUInt16Number inputNumber = *(const cmsUInt16Number *)data;

    // Call the function-under-test
    cmsUInt16Number result = cmsEvalToneCurve16(toneCurve, inputNumber);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}