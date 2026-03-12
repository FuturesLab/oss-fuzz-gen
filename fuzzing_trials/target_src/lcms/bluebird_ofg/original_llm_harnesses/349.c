#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient for cmsUInt16Number array
    if (size < sizeof(cmsUInt16Number) * 3) {
        return 0;
    }

    // Initialize variables
    cmsCIELab lab;
    const cmsUInt16Number *encoded = (const cmsUInt16Number *)data;

    // Call the function under test
    cmsLabEncoded2Float(&lab, encoded);

    return 0;
}