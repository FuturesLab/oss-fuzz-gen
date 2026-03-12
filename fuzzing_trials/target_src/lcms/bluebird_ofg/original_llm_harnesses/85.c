#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure there is enough data for cmsCIELab and cmsUInt16Number
    if (size < sizeof(cmsCIELab) + sizeof(cmsUInt16Number) * 3) {
        return 0;
    }

    // Initialize cmsCIELab structure
    cmsCIELab lab;
    lab.L = 0.0;
    lab.a = 0.0;
    lab.b = 0.0;

    // Initialize cmsUInt16Number array
    const cmsUInt16Number *encodedData = (const cmsUInt16Number *)(data);

    // Call the function-under-test
    cmsLabEncoded2FloatV2(&lab, encodedData);

    return 0;
}