#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to fill cmsCIELCh structure
    if (size < sizeof(cmsCIELCh)) {
        return 0;
    }

    // Initialize cmsCIELCh structure from input data
    cmsCIELCh lch;
    memcpy(&lch, data, sizeof(cmsCIELCh));

    // Initialize cmsCIELab structure to store the result
    cmsCIELab lab;

    // Call the function under test
    cmsLCh2Lab(&lab, &lch);

    return 0;
}