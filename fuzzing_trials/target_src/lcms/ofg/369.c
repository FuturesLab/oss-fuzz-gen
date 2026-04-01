#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for our needs
    if (size < sizeof(cmsUInt32Number) + 3 * 32 + 2 * sizeof(cmsUInt16Number)) {
        return 0;
    }

    // Initialize the parameters for cmsNamedColorInfo
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(NULL, 1, 32, 32, 32);
    if (namedColorList == NULL) {
        return 0;
    }

    cmsUInt32Number index = *((cmsUInt32Number *)data);
    data += sizeof(cmsUInt32Number);

    char name[32];
    char prefix[32];
    char suffix[32];
    memcpy(name, data, 32);
    data += 32;
    memcpy(prefix, data, 32);
    data += 32;
    memcpy(suffix, data, 32);
    data += 32;

    cmsUInt16Number pcs[3];
    cmsUInt16Number device[3];
    memcpy(pcs, data, sizeof(cmsUInt16Number) * 3);
    data += sizeof(cmsUInt16Number) * 3;
    memcpy(device, data, sizeof(cmsUInt16Number) * 3);

    // Call the function under test
    cmsBool result = cmsNamedColorInfo(namedColorList, index, name, prefix, suffix, pcs, device);

    // Free the allocated named color list
    cmsFreeNamedColorList(namedColorList);

    return 0;
}