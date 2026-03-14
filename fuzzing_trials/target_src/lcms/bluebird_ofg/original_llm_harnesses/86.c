#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt16Number) * 3) {
        return 0; // Not enough data to fill cmsUInt16Number array
    }

    cmsCIELab lab;
    cmsUInt16Number encoded[3];

    // Initialize encoded array with data from the input
    for (int i = 0; i < 3; ++i) {
        encoded[i] = (cmsUInt16Number)((data[i * 2] << 8) | data[i * 2 + 1]);
    }

    // Call the function under test
    cmsLabEncoded2FloatV2(&lab, encoded);

    return 0;
}