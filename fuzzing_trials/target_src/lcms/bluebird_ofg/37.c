#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsUInt16Number encodedLab[3]; // Array to hold the encoded Lab values
    cmsCIELab inputLab;

    // Ensure size is sufficient for initializing cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize cmsCIELab structure from data
    const float *floatData = (const float *)data;
    inputLab.L = floatData[0];
    inputLab.a = floatData[1];
    inputLab.b = floatData[2];

    // Call the function-under-test
    cmsFloat2LabEncodedV2(encodedLab, &inputLab);

    return 0;
}