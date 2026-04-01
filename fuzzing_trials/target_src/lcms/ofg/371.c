#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_371(const uint8_t *data, size_t size) {
    // Ensure there is enough data to fill two cmsCIELab structures
    if (size < 2 * sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize two cmsCIELab structures using the input data
    cmsCIELab lab1, lab2;

    // Copy data into the first cmsCIELab structure
    for (size_t i = 0; i < sizeof(cmsCIELab); i++) {
        ((uint8_t*)&lab1)[i] = data[i];
    }

    // Copy data into the second cmsCIELab structure
    for (size_t i = 0; i < sizeof(cmsCIELab); i++) {
        ((uint8_t*)&lab2)[i] = data[i + sizeof(cmsCIELab)];
    }

    // Call the function-under-test
    cmsFloat64Number deltaE = cmsDeltaE(&lab1, &lab2);

    // Use deltaE to prevent compiler optimizations
    (void)deltaE;

    return 0;
}