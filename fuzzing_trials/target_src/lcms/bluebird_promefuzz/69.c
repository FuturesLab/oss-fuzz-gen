#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include "/src/lcms/include/lcms2_plugin.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static cmsContext CreateTestContext() {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsCreateContext
    return cmsCreateContext(NULL, (void *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static void* Test_cmsDupMem(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return NULL;
    }
    
    cmsUInt32Number dupSize = *(cmsUInt32Number*)Data;
    if (dupSize > Size - sizeof(cmsUInt32Number)) {
        return NULL;
    }
    
    const void* original = Data + sizeof(cmsUInt32Number);
    return _cmsDupMem(context, original, dupSize);
}

static cmsHPROFILE Test_cmsOpenProfileFromMemTHR(cmsContext context, const uint8_t *Data, size_t Size) {

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsOpenProfileFromMemTHR
    return cmsOpenProfileFromMemTHR(context, Data, cmsPERCEPTUAL_BLACK_Y);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static cmsHANDLE Test_cmsIT8LoadFromMem(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    } // Ensure len is not zero to avoid assertion failure
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

int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    cmsContext context = CreateTestContext();
    if (!context) {
        return 0;
    }

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