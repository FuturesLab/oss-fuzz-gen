#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to fill a cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize cmsCIELab with data from the fuzzer
    cmsCIELab lab;
    const cmsCIELab* labInput = (const cmsCIELab*)data;

    // Initialize cmsCIELCh to store the output
    cmsCIELCh lchOutput;

    // Call the function-under-test
    cmsLab2LCh(&lchOutput, labInput);

    return 0;
}