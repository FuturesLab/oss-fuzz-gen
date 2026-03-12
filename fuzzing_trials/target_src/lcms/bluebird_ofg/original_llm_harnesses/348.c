#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_348(const uint8_t *data, size_t size) {
    // Ensure there is enough data for cmsCIELab and cmsUInt16Number
    if (size < sizeof(cmsCIELab) + sizeof(cmsUInt16Number)) {
        return 0;
    }

    // Initialize cmsCIELab and cmsUInt16Number
    cmsCIELab lab;
    const cmsUInt16Number *encoded = (const cmsUInt16Number *)data;

    // Call the function under test
    cmsLabEncoded2Float(&lab, encoded);

    return 0;
}