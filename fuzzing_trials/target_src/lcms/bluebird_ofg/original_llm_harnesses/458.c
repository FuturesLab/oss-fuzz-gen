#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_458(const uint8_t *data, size_t size) {
    if (size < 3 * sizeof(uint16_t)) {
        return 0; // Not enough data to create tone curves
    }

    // Declare and initialize the cmsToneCurve array
    cmsToneCurve *toneCurves[3];

    // Use the input data to create tone curves
    for (int i = 0; i < 3; ++i) {
        uint16_t gammaValue = ((uint16_t *)data)[i]; // Use data to influence gamma
        toneCurves[i] = cmsBuildGamma(NULL, gammaValue / 65535.0 * 10.0); // Scale gamma to a reasonable range
        if (toneCurves[i] == NULL) {
            // If allocation fails, free any allocated tone curves and return
            for (int j = 0; j < i; ++j) {
                cmsFreeToneCurve(toneCurves[j]);
            }
            return 0;
        }
    }

    // Call the function under test
    cmsFreeToneCurveTriple(toneCurves);

    return 0;
}