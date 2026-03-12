// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsAllocProfileSequenceDescription at cmsnamed.c:985:19 in lcms2.h
// cmsFreeProfileSequenceDescription at cmsnamed.c:1017:16 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsMallocZero at cmserr.c:272:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsCalloc at cmserr.c:279:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsContext createContext() {
    return cmsCreateContext(NULL, NULL);
}

static void fuzz_cmsAllocProfileSequenceDescription(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    cmsUInt32Number n = Data[0] % 256; // Ensure n is between 0 and 255
    cmsSEQ* seq = cmsAllocProfileSequenceDescription(context, n);
    if (seq) {
        // Free the allocated sequence
        cmsFreeProfileSequenceDescription(seq);
    }
}

static void fuzz__cmsRealloc(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    cmsUInt32Number newSize = *(cmsUInt32Number*)Data;
    void* ptr = _cmsMalloc(context, 10); // Initial allocation
    void* newPtr = _cmsRealloc(context, ptr, newSize);
    if (newPtr) {
        _cmsFree(context, newPtr);
    } else {
        _cmsFree(context, ptr);
    }
}

static void fuzz__cmsMalloc(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    cmsUInt32Number size = *(cmsUInt32Number*)Data;
    void* ptr = _cmsMalloc(context, size);
    if (ptr) {
        _cmsFree(context, ptr);
    }
}

static void fuzz__cmsMallocZero(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 4) return;
    cmsUInt32Number size = *(cmsUInt32Number*)Data;
    void* ptr = _cmsMallocZero(context, size);
    if (ptr) {
        _cmsFree(context, ptr);
    }
}

static void fuzz__cmsCalloc(cmsContext context, const uint8_t *Data, size_t Size) {
    if (Size < 8) return;
    cmsUInt32Number num = *(cmsUInt32Number*)Data;
    cmsUInt32Number size = *(cmsUInt32Number*)(Data + 4);
    void* ptr = _cmsCalloc(context, num, size);
    if (ptr) {
        _cmsFree(context, ptr);
    }
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    cmsContext context = createContext();
    if (!context) return 0;

    fuzz_cmsAllocProfileSequenceDescription(context, Data, Size);
    fuzz__cmsRealloc(context, Data, Size);
    fuzz__cmsMalloc(context, Data, Size);
    fuzz__cmsMallocZero(context, Data, Size);
    fuzz__cmsCalloc(context, Data, Size);

    cmsDeleteContext(context);
    return 0;
}