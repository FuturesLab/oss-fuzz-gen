#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract values for cmsCIELab structures and cmsFloat64Number
    if (size < sizeof(cmsCIELab) * 2 + sizeof(cmsFloat64Number) * 3) {
        return 0;
    }

    // Initialize cmsCIELab structures
    cmsCIELab Lab1;
    cmsCIELab Lab2;

    // Extract values for Lab1
    Lab1.L = *((cmsFloat64Number *)(data));
    Lab1.a = *((cmsFloat64Number *)(data + sizeof(cmsFloat64Number)));
    Lab1.b = *((cmsFloat64Number *)(data + 2 * sizeof(cmsFloat64Number)));

    // Extract values for Lab2
    Lab2.L = *((cmsFloat64Number *)(data + 3 * sizeof(cmsFloat64Number)));
    Lab2.a = *((cmsFloat64Number *)(data + 4 * sizeof(cmsFloat64Number)));
    Lab2.b = *((cmsFloat64Number *)(data + 5 * sizeof(cmsFloat64Number)));

    // Extract cmsFloat64Number values
    cmsFloat64Number K_L = *((cmsFloat64Number *)(data + 6 * sizeof(cmsFloat64Number)));
    cmsFloat64Number K_C = *((cmsFloat64Number *)(data + 7 * sizeof(cmsFloat64Number)));
    cmsFloat64Number K_H = *((cmsFloat64Number *)(data + 8 * sizeof(cmsFloat64Number)));

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsCIE2000DeltaE(&Lab1, &Lab2, K_L, K_C, K_H);

    // Use deltaE in some way to avoid compiler optimizations
    volatile cmsFloat64Number result = deltaE;
    (void)result;

    return 0;
}