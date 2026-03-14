#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Ensure there's enough data to fill a cmsCIEXYZ structure
    if (size < sizeof(cmsCIEXYZ)) {
        return 0;
    }

    // Initialize the cmsCIEXYZ structure
    cmsCIEXYZ xyz;
    cmsUInt16Number encoded[3];

    // Copy data into the cmsCIEXYZ structure
    // Assuming data is in the correct format and size is sufficient
    memcpy(&xyz, data, sizeof(cmsCIEXYZ));

    // Call the function-under-test
    cmsFloat2XYZEncoded(encoded, &xyz);

    return 0;
}