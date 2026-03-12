#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to populate cmsCIELab
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    cmsUInt16Number encodedLab[3]; // Array to hold the encoded Lab values
    cmsCIELab lab;

    // Initialize the cmsCIELab structure from the input data
    // We assume the input data is large enough to fill a cmsCIELab structure
    const float *floatData = (const float *)data;
    lab.L = floatData[0];
    lab.a = floatData[1];
    lab.b = floatData[2];

    // Call the function-under-test
    cmsFloat2LabEncodedV2(encodedLab, &lab);

    return 0;
}