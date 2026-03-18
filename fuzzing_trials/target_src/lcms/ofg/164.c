#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Initialize variables for cmsAppendNamedColor
    cmsNAMEDCOLORLIST *namedColorList;
    const char *colorName;
    cmsUInt16Number pcs[3];
    cmsUInt16Number device[3];

    // Ensure data is large enough to extract necessary information
    // We need at least 6 bytes for pcs and device values, plus some bytes for a color name
    if (size < 6 + 1) { // 1 byte for at least a single character color name
        return 0;
    }

    // Initialize namedColorList
    namedColorList = cmsAllocNamedColorList(NULL, 1, 3, "Prefix", "Suffix");
    if (namedColorList == NULL) {
        return 0;
    }

    // Extract colorName from data
    colorName = (const char *)(data);

    // Extract pcs values from data
    pcs[0] = (cmsUInt16Number)data[size - 6];
    pcs[1] = (cmsUInt16Number)data[size - 5];
    pcs[2] = (cmsUInt16Number)data[size - 4];

    // Extract device values from data
    device[0] = (cmsUInt16Number)data[size - 3];
    device[1] = (cmsUInt16Number)data[size - 2];
    device[2] = (cmsUInt16Number)data[size - 1];

    // Call the function-under-test
    cmsBool result = cmsAppendNamedColor(namedColorList, colorName, pcs, device);

    // Clean up
    cmsFreeNamedColorList(namedColorList);

    return 0;
}