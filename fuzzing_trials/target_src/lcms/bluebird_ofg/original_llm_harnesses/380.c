#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_380(const uint8_t *data, size_t size) {
    cmsCIELab lab1;
    cmsCIELab lab2;

    if (size < 6 * sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize lab1
    lab1.L = *(cmsFloat64Number *)(data);
    lab1.a = *(cmsFloat64Number *)(data + sizeof(cmsFloat64Number));
    lab1.b = *(cmsFloat64Number *)(data + 2 * sizeof(cmsFloat64Number));

    // Initialize lab2
    lab2.L = *(cmsFloat64Number *)(data + 3 * sizeof(cmsFloat64Number));
    lab2.a = *(cmsFloat64Number *)(data + 4 * sizeof(cmsFloat64Number));
    lab2.b = *(cmsFloat64Number *)(data + 5 * sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsBFDdeltaE(&lab1, &lab2);

    // Use deltaE in some way to prevent compiler optimizations from removing the call
    volatile cmsFloat64Number result = deltaE;
    (void)result;

    return 0;
}