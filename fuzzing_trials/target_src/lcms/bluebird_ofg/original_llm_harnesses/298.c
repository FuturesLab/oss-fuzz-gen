#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;
    cmsIOHANDLER *ioHandler = NULL;
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number result;

    if (context == NULL) {
        return 0;
    }

    // Create a memory-based IO handler
    ioHandler = cmsOpenIOhandlerFromMem(context, (void *)data, size, "r");
    if (ioHandler == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Create a fake profile for testing purposes
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        cmsCloseIOhandler(ioHandler);
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    result = cmsSaveProfileToIOhandler(hProfile, ioHandler);

    // Clean up
    cmsCloseIOhandler(ioHandler);
    cmsCloseProfile(hProfile);
    cmsDeleteContext(context);

    return 0;
}