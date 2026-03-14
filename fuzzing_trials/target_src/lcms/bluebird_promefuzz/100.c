#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"

static cmsContext createDummyContext() {
    // Create a dummy context for fuzzing
    return (cmsContext)malloc(sizeof(void*)); // Allocate a pointer-sized memory as a dummy context
}

static void destroyDummyContext(cmsContext context) {
    free(context);
}

int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = createDummyContext();
    if (!context) return 0;

    // Fuzz cmsCreateXYZProfileTHR
    cmsHPROFILE profileXYZ = cmsCreateXYZProfileTHR(context);
    if (profileXYZ) {
        cmsSetHeaderFlags(profileXYZ, Data[0]);
        cmsCloseProfile(profileXYZ);
    }

    // Fuzz cmsOpenProfileFromMemTHR
    cmsHPROFILE profileMem = cmsOpenProfileFromMemTHR(context, Data, Size);
    if (profileMem) {
        cmsSetHeaderFlags(profileMem, Data[0]);
        cmsCloseProfile(profileMem);
    }

    // Fuzz _cmsMalloc
    void* allocatedMemory = _cmsMalloc(context, Size);
    if (allocatedMemory) {
        memset(allocatedMemory, 0, Size);
        free(allocatedMemory);
    }

    // Fuzz cmsSignalError
    cmsSignalError(context, Data[0], "Fuzzing error code: %u", Data[0]);

    // Fuzz cmsCreateTransformTHR
    cmsHPROFILE inputProfile = cmsCreateXYZProfileTHR(context);
    cmsHPROFILE outputProfile = cmsCreateXYZProfileTHR(context);
    if (inputProfile && outputProfile) {
        cmsHTRANSFORM transform = cmsCreateTransformTHR(context, inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
        if (transform) {
            cmsDeleteTransform(transform);
        }
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
    }

    destroyDummyContext(context);
    return 0;
}