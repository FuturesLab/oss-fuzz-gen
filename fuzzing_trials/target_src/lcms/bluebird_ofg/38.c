#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    cmsCIELab Lab1, Lab2;
    cmsFloat64Number l, c;
    
    if (size < sizeof(cmsCIELab) * 2 + sizeof(cmsFloat64Number) * 2) {
        return 0;
    }

    // Initialize Lab1 and Lab2 from input data
    const cmsCIELab* inputLab1 = (const cmsCIELab*)data;
    const cmsCIELab* inputLab2 = (const cmsCIELab*)(data + sizeof(cmsCIELab));
    
    Lab1.L = inputLab1->L;
    Lab1.a = inputLab1->a;
    Lab1.b = inputLab1->b;

    Lab2.L = inputLab2->L;
    Lab2.a = inputLab2->a;
    Lab2.b = inputLab2->b;

    // Initialize l and c from input data
    l = *(const cmsFloat64Number*)(data + sizeof(cmsCIELab) * 2);
    c = *(const cmsFloat64Number*)(data + sizeof(cmsCIELab) * 2 + sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number result = cmsCMCdeltaE(&Lab1, &Lab2, l, c);

    return 0;
}