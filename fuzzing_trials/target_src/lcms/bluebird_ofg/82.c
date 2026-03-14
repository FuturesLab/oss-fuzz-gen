#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for cmsXYZEncoded2Float
    cmsCIEXYZ xyz;
    cmsUInt16Number encoded[3];

    // Ensure that the size is sufficient to extract the required data
    if (size < sizeof(encoded)) {
        return 0;
    }

    // Initialize the encoded values from the input data
    for (int i = 0; i < 3; i++) {
        encoded[i] = ((cmsUInt16Number)data[i*2] << 8) | data[i*2 + 1];
    }

    // Call the function-under-test
    cmsXYZEncoded2Float(&xyz, encoded);

    return 0;
}