#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_493(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);
    if (profile == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt32Number intent = 0;  // Rendering intent
    cmsUInt32Number flags = 0;   // Flags
    cmsUInt32Number bufferSize = 1024;
    void *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        cmsCloseProfile(profile);
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt32Number result = cmsGetPostScriptCRD(context, profile, intent, flags, buffer, bufferSize);

    // Clean up
    free(buffer);
    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}