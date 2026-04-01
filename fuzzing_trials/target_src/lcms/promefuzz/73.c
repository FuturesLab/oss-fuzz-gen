// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsDupMem at cmserr.c:302:17 in lcms2_plugin.h
// cmsOpenProfileFromMemTHR at cmsio0.c:1272:23 in lcms2.h
// cmsIT8LoadFromMem at cmscgats.c:2556:22 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// _cmsMallocZero at cmserr.c:272:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsIT8Free at cmscgats.c:1170:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
#include <lcms2_plugin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static cmsContext CreateTestContext() {
    return cmsCreateContext(NULL, NULL);
}

static void* Test_cmsDupMem(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return NULL;
    
    cmsUInt32Number dupSize = *(cmsUInt32Number*)Data;
    if (dupSize > Size - sizeof(cmsUInt32Number)) return NULL;
    
    const void* original = Data + sizeof(cmsUInt32Number);
    return _cmsDupMem(context, original, dupSize);
}

static cmsHPROFILE Test_cmsOpenProfileFromMemTHR(cmsContext context, const uint8_t *Data, size_t Size) {
    return cmsOpenProfileFromMemTHR(context, Data, (cmsUInt32Number)Size);
}

static cmsHANDLE Test_cmsIT8LoadFromMem(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL; // Ensure len is not zero to avoid assertion failure
    return cmsIT8LoadFromMem(context, Data, (cmsUInt32Number)Size);
}

static void* Test_cmsMalloc(cmsContext context, cmsUInt32Number size) {
    return _cmsMalloc(context, size);
}

static void* Test_cmsMallocZero(cmsContext context, cmsUInt32Number size) {
    return _cmsMallocZero(context, size);
}

static void Test_cmsFree(cmsContext context, void* ptr) {
    _cmsFree(context, ptr);
}

int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    cmsContext context = CreateTestContext();
    if (!context) return 0;

    // Test _cmsDupMem
    void* dupMem = Test_cmsDupMem(context, Data, Size);
    if (dupMem) {
        Test_cmsFree(context, dupMem);
    }

    // Test cmsOpenProfileFromMemTHR
    cmsHPROFILE profile = Test_cmsOpenProfileFromMemTHR(context, Data, Size);
    if (profile) {
        cmsCloseProfile(profile);
    }

    // Test cmsIT8LoadFromMem
    cmsHANDLE it8Handle = Test_cmsIT8LoadFromMem(context, Data, Size);
    if (it8Handle) {
        cmsIT8Free(it8Handle);
    }

    // Test _cmsMalloc and _cmsMallocZero
    void* mem = Test_cmsMalloc(context, (cmsUInt32Number)Size);
    if (mem) {
        Test_cmsFree(context, mem);
    }

    void* memZero = Test_cmsMallocZero(context, (cmsUInt32Number)Size);
    if (memZero) {
        Test_cmsFree(context, memZero);
    }

    cmsDeleteContext(context);
    return 0;
}