#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsCIExyY whitePoint;
    cmsFloat64Number temperature;

    // Ensure that there is enough data to extract a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize temperature using the input data
    // Note: This assumes that data is aligned and large enough to be safely cast
    temperature = *(const cmsFloat64Number *)data;

    // Call the function under test
    cmsBool result = cmsWhitePointFromTemp(&whitePoint, temperature);

    // Use the result to avoid compiler optimizations that skip the function call
    if (result) {
        // Do something with whitePoint if needed
    }

    return 0;
}