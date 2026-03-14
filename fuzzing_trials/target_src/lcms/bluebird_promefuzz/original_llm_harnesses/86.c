// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
// cmsCreate_sRGBProfileTHR at cmsvirt.c:653:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateProfilePlaceholder at cmsio0.c:526:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

static cmsContext createInitialContext() {
    return cmsCreateContext(NULL, NULL);
}

static void fuzzCmsDictAlloc(cmsContext context) {
    cmsHANDLE dict = cmsDictAlloc(context);
    if (dict) {
        cmsDictFree(dict);
    }
}

static void fuzzCmsGBDAlloc(cmsContext context) {
    cmsHANDLE gbd = cmsGBDAlloc(context);
    if (gbd) {
        cmsGBDFree(gbd);
    }
}

static void fuzzCmsCreateSRGBProfileTHR(cmsContext context) {
    cmsHPROFILE profile = cmsCreate_sRGBProfileTHR(context);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzzCmsDupContext(cmsContext context) {
    cmsContext newContext = cmsDupContext(context, NULL);
    if (newContext) {
        cmsDeleteContext(newContext);
    }
}

static void fuzzCmsCreateProfilePlaceholder(cmsContext context) {
    cmsHPROFILE placeholder = cmsCreateProfilePlaceholder(context);
    if (placeholder) {
        cmsCloseProfile(placeholder);
    }
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    cmsContext context = createInitialContext();
    if (context == NULL) {
        return 0;
    }

    fuzzCmsDictAlloc(context);
    fuzzCmsGBDAlloc(context);
    fuzzCmsCreateSRGBProfileTHR(context);
    fuzzCmsDupContext(context);
    fuzzCmsCreateProfilePlaceholder(context);

    cmsDeleteContext(context);
    return 0;
}