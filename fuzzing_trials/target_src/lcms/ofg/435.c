#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_435(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for cmsUInt16Number array
    if (size < sizeof(cmsUInt16Number) * 3) {
        return 0;
    }

    // Declare and initialize variables
    cmsCIEXYZ xyz;
    const cmsUInt16Number *encoded = (const cmsUInt16Number *)data;

    // Call the function under test
    cmsXYZEncoded2Float(&xyz, encoded);

    return 0;
}