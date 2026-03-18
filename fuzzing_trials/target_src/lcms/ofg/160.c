#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Declare and initialize cmsCIELab and cmsCIELCh structures
    cmsCIELab lab;
    cmsCIELCh lch;

    // Ensure that the size is sufficient to fill the cmsCIELCh structure
    if (size < sizeof(cmsCIELCh)) {
        return 0;
    }

    // Populate the cmsCIELCh structure with data from the input
    const cmsCIELCh *inputLCh = (const cmsCIELCh *)data;

    // Copy the input data into the lch structure
    lch.L = inputLCh->L;
    lch.C = inputLCh->C;
    lch.h = inputLCh->h;

    // Call the function-under-test
    cmsLCh2Lab(&lab, &lch);

    return 0;
}