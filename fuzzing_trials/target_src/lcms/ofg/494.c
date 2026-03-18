#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_494(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number intent = 0; // Use a valid intent value
    cmsUInt32Number flags = 0; // Use default flags
    char buffer[1024]; // Allocate a buffer for the CRD
    cmsUInt32Number bufferSize = sizeof(buffer);

    if (profile != NULL) {
        cmsGetPostScriptCRD(context, profile, intent, flags, buffer, bufferSize);
        cmsCloseProfile(profile);
    }

    cmsDeleteContext(context);
    return 0;
}