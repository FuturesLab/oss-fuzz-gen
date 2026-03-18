#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_446(const uint8_t *data, size_t size) {
    // Declare and initialize all variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsPSResourceType resourceType = cmsPS_RESOURCE_CSA;
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;
    cmsIOHANDLER *iohandler = cmsOpenIOhandlerFromFile(context, "output.ps", "w");

    // Check if the profile and iohandler are valid
    if (hProfile == NULL || iohandler == NULL) {
        if (hProfile != NULL) cmsCloseProfile(hProfile);
        if (iohandler != NULL) cmsCloseIOhandler(iohandler);
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number result = cmsGetPostScriptColorResource(context, resourceType, hProfile, intent, flags, iohandler);

    // Clean up resources
    cmsCloseProfile(hProfile);
    cmsCloseIOhandler(iohandler);
    cmsDeleteContext(context);

    return 0;
}