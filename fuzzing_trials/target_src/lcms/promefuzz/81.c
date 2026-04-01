// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsDestroyMutex at cmserr.c:636:16 in lcms2_plugin.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsLockMutex at cmserr.c:646:19 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsCreateMutex at cmserr.c:627:17 in lcms2_plugin.h
// _cmsUnlockMutex at cmserr.c:655:16 in lcms2_plugin.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsContext createDummyContext() {
    // Create a dummy context for testing purposes
    return cmsCreateContext(NULL, NULL);
}

static void fuzzDestroyMutex(cmsContext context, void* mutex) {
    _cmsDestroyMutex(context, mutex);
}

static void fuzzDupContext(cmsContext context) {
    cmsContext newContext = cmsDupContext(context, NULL);
    if (newContext) {
        cmsDeleteContext(newContext);
    }
}

static void fuzzLockMutex(cmsContext context, void* mutex) {
    _cmsLockMutex(context, mutex);
}

static void fuzzDeleteContext(cmsContext context) {
    cmsDeleteContext(context);
}

static void* fuzzCreateMutex(cmsContext context) {
    return _cmsCreateMutex(context);
}

static void fuzzUnlockMutex(cmsContext context, void* mutex) {
    _cmsUnlockMutex(context, mutex);
}

int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) return 0;

    cmsContext context = createDummyContext();
    if (!context) return 0;

    void* mutex = fuzzCreateMutex(context);
    if (mutex) {
        fuzzLockMutex(context, mutex);
        fuzzUnlockMutex(context, mutex);
        fuzzDestroyMutex(context, mutex);
    }

    fuzzDupContext(context);
    fuzzDeleteContext(context);

    return 0;
}