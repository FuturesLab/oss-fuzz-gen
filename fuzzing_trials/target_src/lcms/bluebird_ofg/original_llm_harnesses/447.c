#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_447(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsPSResourceType resourceType = cmsPS_RESOURCE_CSA;
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;
    
    // Allocate a buffer for IOHANDLER
    void *buffer = malloc(size);
    if (buffer == NULL) {
        cmsDeleteContext(context);
        return 0;
    }
    
    cmsIOHANDLER *ioHandler = cmsOpenIOhandlerFromMem(context, buffer, size, "w");
    
    if (profile == NULL || ioHandler == NULL) {
        if (ioHandler != NULL) cmsCloseIOhandler(ioHandler);
        cmsDeleteContext(context);
        free(buffer);
        return 0;
    }

    cmsUInt32Number result = cmsGetPostScriptColorResource(context, resourceType, profile, intent, flags, ioHandler);

    // Clean up
    cmsCloseIOhandler(ioHandler);
    cmsCloseProfile(profile);
    cmsDeleteContext(context);
    free(buffer);

    return 0;
}