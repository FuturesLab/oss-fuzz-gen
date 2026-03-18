#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for two cmsCIELab structures
    if (size < 2 * sizeof(cmsCIELab)) {
        return 0;
    }

    // Create two cmsCIELab structures from the input data
    cmsCIELab lab1, lab2;

    // Copy data into the cmsCIELab structures
    // Ensure proper casting and alignment
    const cmsCIELab* inputLab1 = (const cmsCIELab*)data;
    const cmsCIELab* inputLab2 = (const cmsCIELab*)(data + sizeof(cmsCIELab));

    // Assign values to lab1 and lab2
    lab1.L = inputLab1->L;
    lab1.a = inputLab1->a;
    lab1.b = inputLab1->b;

    lab2.L = inputLab2->L;
    lab2.a = inputLab2->a;
    lab2.b = inputLab2->b;

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsCIE94DeltaE(&lab1, &lab2);

    // Use deltaE in some way to avoid compiler optimizations removing the call
    (void)deltaE;

    return 0;
}