#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to populate two cmsCIELab structures
    if (size < 6 * sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Declare and initialize two cmsCIELab structures
    cmsCIELab lab1, lab2;

    // Extract values from the input data for the first cmsCIELab structure
    lab1.L = *((const cmsFloat64Number *)data);
    lab1.a = *((const cmsFloat64Number *)(data + sizeof(cmsFloat64Number)));
    lab1.b = *((const cmsFloat64Number *)(data + 2 * sizeof(cmsFloat64Number)));

    // Extract values from the input data for the second cmsCIELab structure
    lab2.L = *((const cmsFloat64Number *)(data + 3 * sizeof(cmsFloat64Number)));
    lab2.a = *((const cmsFloat64Number *)(data + 4 * sizeof(cmsFloat64Number)));
    lab2.b = *((const cmsFloat64Number *)(data + 5 * sizeof(cmsFloat64Number)));

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsBFDdeltaE(&lab1, &lab2);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)deltaE;

    return 0;
}