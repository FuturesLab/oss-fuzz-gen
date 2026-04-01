#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for two cmsCIELab structures and two cmsFloat64Number values
    if (size < 2 * sizeof(cmsCIELab) + 2 * sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize two cmsCIELab structures
    cmsCIELab lab1;
    cmsCIELab lab2;

    // Copy data into the cmsCIELab structures
    size_t offset = 0;
    memcpy(&lab1, data + offset, sizeof(cmsCIELab));
    offset += sizeof(cmsCIELab);
    memcpy(&lab2, data + offset, sizeof(cmsCIELab));
    offset += sizeof(cmsCIELab);

    // Initialize two cmsFloat64Number values
    cmsFloat64Number param1;
    cmsFloat64Number param2;

    // Copy data into the cmsFloat64Number values
    memcpy(&param1, data + offset, sizeof(cmsFloat64Number));
    offset += sizeof(cmsFloat64Number);
    memcpy(&param2, data + offset, sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number result = cmsCMCdeltaE(&lab1, &lab2, param1, param2);

    // Use the result in some way to avoid any compiler optimizations removing the call
    volatile cmsFloat64Number use_result = result;
    (void)use_result;

    return 0;
}