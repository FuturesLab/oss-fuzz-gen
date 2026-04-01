#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to fill both cmsCIELab and cmsCIELCh structures
    if (size < sizeof(cmsCIELab) + sizeof(cmsCIELCh)) {
        return 0;
    }

    // Initialize the cmsCIELab structure from the input data
    cmsCIELab lab;
    lab.L = ((double)data[0] / 255.0) * 100.0;  // L ranges from 0 to 100
    lab.a = ((double)data[1] - 128.0);          // a ranges from -128 to 127
    lab.b = ((double)data[2] - 128.0);          // b ranges from -128 to 127

    // Initialize an empty cmsCIELCh structure
    cmsCIELCh lch;

    // Call the function-under-test
    cmsLab2LCh(&lch, &lab);

    return 0;
}