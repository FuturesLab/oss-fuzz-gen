#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsInt32Number index = 0; // Initialize index to 0
    cmsToneCurve *toneCurve = NULL;

    // Check if size is sufficient to create a tone curve with at least one entry
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Create a tone curve using the data
    toneCurve = cmsBuildTabulatedToneCurve16(NULL, size / sizeof(uint16_t), (const uint16_t *)data);

    // Ensure toneCurve is not NULL
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsBuildTabulatedToneCurve16 to cmsSmoothToneCurve
    cmsFloat64Number ret_cmsSetAdaptationState_apfue = cmsSetAdaptationState(cmsSPOT_ROUND);
    if (ret_cmsSetAdaptationState_apfue < 0){
    	return 0;
    }

    cmsBool ret_cmsSmoothToneCurve_uiitt = cmsSmoothToneCurve(toneCurve, ret_cmsSetAdaptationState_apfue);
    if (ret_cmsSmoothToneCurve_uiitt < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const cmsCurveSegment *segment = cmsGetToneCurveSegment(index, toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}