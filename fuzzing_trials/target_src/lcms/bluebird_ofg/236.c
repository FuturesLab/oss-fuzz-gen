#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

// Function-under-test
cmsColorSpaceSignature _cmsICCcolorSpace(int);

// Fuzzing harness
int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int); i++) {
        input_value |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    cmsColorSpaceSignature result = _cmsICCcolorSpace(input_value);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}