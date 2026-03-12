// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsGetContextUserData at cmsplugin.c:1021:17 in lcms2.h
// cmsCreate_sRGBProfileTHR at cmsvirt.c:653:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreate_OkLabProfile at cmsvirt.c:690:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGetProfileContextID at cmsio0.c:571:22 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static void fuzz_cmsGetProfileContextID(cmsHPROFILE hProfile) {
    cmsContext contextID = cmsGetProfileContextID(hProfile);
    // Handle contextID if necessary
}

static void fuzz_cmsGetContextUserData(cmsContext contextID) {
    if (contextID) {
        void* userData = cmsGetContextUserData(contextID);
        // Handle userData if necessary
    }
}

static void fuzz_cmsCreate_sRGBProfileTHR(cmsContext contextID) {
    cmsHPROFILE hProfile = cmsCreate_sRGBProfileTHR(contextID);
    if (hProfile) {
        fuzz_cmsGetProfileContextID(hProfile);
        cmsCloseProfile(hProfile);
    }
}

static void fuzz_cmsDupContext(cmsContext contextID) {
    if (contextID) {
        cmsContext newContext = cmsDupContext(contextID, NULL);
        if (newContext) {
            fuzz_cmsGetContextUserData(newContext);
            cmsDeleteContext(newContext);
        }
    }
}

static void fuzz_cmsCreate_OkLabProfile(cmsContext contextID) {
    cmsHPROFILE hProfile = cmsCreate_OkLabProfile(contextID);
    if (hProfile) {
        fuzz_cmsGetProfileContextID(hProfile);
        cmsCloseProfile(hProfile);
    }
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsContext)) return 0;

    cmsContext contextID = cmsCreateContext(NULL, NULL);
    if (!contextID) return 0;

    fuzz_cmsGetContextUserData(contextID);
    fuzz_cmsCreate_sRGBProfileTHR(contextID);
    fuzz_cmsDupContext(contextID);
    fuzz_cmsCreate_OkLabProfile(contextID);

    cmsDeleteContext(contextID);
    return 0;
}