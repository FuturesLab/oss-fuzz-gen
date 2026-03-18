#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_428(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsCIELab) + 4 * sizeof(double)) {
        return 0;
    }

    cmsCIELab lab;
    double d1, d2, d3, d4;

    // Initialize the cmsCIELab structure
    lab.L = (double)data[0];
    lab.a = (double)data[1];
    lab.b = (double)data[2];

    // Extract doubles from the input data
    d1 = *((double*)(data + sizeof(cmsCIELab)));
    d2 = *((double*)(data + sizeof(cmsCIELab) + sizeof(double)));
    d3 = *((double*)(data + sizeof(cmsCIELab) + 2 * sizeof(double)));
    d4 = *((double*)(data + sizeof(cmsCIELab) + 3 * sizeof(double)));

    // Call the function-under-test
    cmsBool result = cmsDesaturateLab(&lab, d1, d2, d3, d4);

    return 0;
}