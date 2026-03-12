#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"

static cmsHPROFILE create_dummy_profile() {
    // Create a dummy profile for testing purposes
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    return profile;
}

static void cleanup(cmsContext context, cmsHPROFILE profile, void* buffer) {
    if (profile) {
        cmsCloseProfile(profile);
    }
    if (buffer) {
        _cmsFree(context, buffer);
    }
}

int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2) {
        return 0; // Not enough data to proceed
    }

    cmsContext context = NULL; // Use default context
    cmsHPROFILE profile = create_dummy_profile();
    if (!profile) {
        return 0;
    }

    cmsUInt32Number intent = *(cmsUInt32Number*)Data;
    cmsUInt32Number flags = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number));

    // First call to cmsGetPostScriptCSA with NULL buffer
    cmsUInt32Number bufferLen = cmsGetPostScriptCSA(context, profile, intent, flags, NULL, 0);

    // Allocate memory using _cmsMalloc
    void* buffer = _cmsMalloc(context, bufferLen);
    if (!buffer) {
        cleanup(context, profile, NULL);
        return 0;
    }

    // Second call to cmsGetPostScriptCSA with allocated buffer
    cmsUInt32Number bytesWritten = cmsGetPostScriptCSA(context, profile, intent, flags, buffer, bufferLen);
    if (bytesWritten == 0) {
        cleanup(context, profile, buffer);
        return 0;
    }

    // Clean up allocated resources
    cleanup(context, profile, buffer);

    return 0;
}