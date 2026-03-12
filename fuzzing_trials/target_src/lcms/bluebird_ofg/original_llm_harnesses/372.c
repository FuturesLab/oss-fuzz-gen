#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_372(const uint8_t *data, size_t size) {
    cmsCIELab Lab1;
    cmsCIELab Lab2;

    // Ensure that the size is sufficient to fill two cmsCIELab structures
    if (size < 2 * sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize Lab1 and Lab2 using the input data
    // Assuming data is large enough to fill two cmsCIELab structures
    const cmsCIELab *inputLab1 = (const cmsCIELab *)data;
    const cmsCIELab *inputLab2 = (const cmsCIELab *)(data + sizeof(cmsCIELab));

    Lab1.L = inputLab1->L;
    Lab1.a = inputLab1->a;
    Lab1.b = inputLab1->b;

    Lab2.L = inputLab2->L;
    Lab2.a = inputLab2->a;
    Lab2.b = inputLab2->b;

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsDeltaE(&Lab1, &Lab2);

    // Use the result in some way to avoid compiler optimizations that remove the call
    volatile cmsFloat64Number result = deltaE;
    (void)result;

    return 0;
}