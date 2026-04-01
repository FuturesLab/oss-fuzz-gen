#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize the cmsCIELab structure from the input data
    cmsCIELab lab;
    const cmsCIELab *labPtr = (const cmsCIELab *)data;

    // Copy data into lab structure
    lab.L = labPtr->L;
    lab.a = labPtr->a;
    lab.b = labPtr->b;

    // Initialize cmsUInt16Number array
    cmsUInt16Number encoded[3] = {0};

    // Call the function-under-test
    cmsFloat2LabEncoded(encoded, &lab);

    return 0;
}