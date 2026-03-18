#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure there is enough data for two cmsCIELab structs and three cmsFloat64Number values
    if (size < 2 * sizeof(cmsCIELab) + 3 * sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize two cmsCIELab structures
    cmsCIELab lab1, lab2;
    cmsFloat64Number kL, kC, kH;

    // Copy data into the first cmsCIELab structure
    const cmsCIELab *inputLab1 = (const cmsCIELab *)data;
    lab1.L = inputLab1->L;
    lab1.a = inputLab1->a;
    lab1.b = inputLab1->b;

    // Move data pointer forward
    data += sizeof(cmsCIELab);

    // Copy data into the second cmsCIELab structure
    const cmsCIELab *inputLab2 = (const cmsCIELab *)data;
    lab2.L = inputLab2->L;
    lab2.a = inputLab2->a;
    lab2.b = inputLab2->b;

    // Move data pointer forward
    data += sizeof(cmsCIELab);

    // Copy data into the three cmsFloat64Number values
    kL = *((const cmsFloat64Number *)data);
    data += sizeof(cmsFloat64Number);

    kC = *((const cmsFloat64Number *)data);
    data += sizeof(cmsFloat64Number);

    kH = *((const cmsFloat64Number *)data);

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsCIE2000DeltaE(&lab1, &lab2, kL, kC, kH);

    // Use deltaE to avoid unused variable warning
    (void)deltaE;

    return 0;
}