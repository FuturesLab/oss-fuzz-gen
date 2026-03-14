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
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    return hProfile;
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3) {
        return 0; // Not enough data to proceed
    }

    cmsContext ContextID = NULL;
    cmsHPROFILE hProfile = create_dummy_profile();
    cmsUInt32Number Intent = *(cmsUInt32Number*)Data;
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number dwBufferLen = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsUInt32Number));

    // First call to cmsGetPostScriptCRD with a NULL buffer
    cmsUInt32Number bytesWritten1 = cmsGetPostScriptCRD(ContextID, hProfile, Intent, dwFlags, NULL, 0);

    // Allocate memory using _cmsMalloc

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetPostScriptCRD to cmsSetHeaderAttributes
    cmsHPROFILE ret_cmsCreateLab4Profile_rwpmn = cmsCreateLab4Profile(NULL);

    cmsSetHeaderAttributes(ret_cmsCreateLab4Profile_rwpmn, bytesWritten1);

    // End mutation: Producer.APPEND_MUTATOR

    void* Buffer = _cmsMalloc(ContextID, dwBufferLen);

    // Second call to cmsGetPostScriptCRD with an allocated buffer
    if (Buffer != NULL) {
        cmsUInt32Number bytesWritten2 = cmsGetPostScriptCRD(ContextID, hProfile, Intent, dwFlags, Buffer, dwBufferLen);
    }

    // Free the allocated memory
    _cmsFree(ContextID, Buffer);

    // Cleanup
    if (hProfile != NULL) {
        cmsCloseProfile(hProfile);
    }
    return 0;
}