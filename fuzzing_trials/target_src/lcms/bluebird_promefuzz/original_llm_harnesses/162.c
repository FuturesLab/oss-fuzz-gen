// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsAllocProfileSequenceDescription at cmsnamed.c:985:19 in lcms2.h
// cmsDupProfileSequenceDescription at cmsnamed.c:1037:19 in lcms2.h
// cmsFreeProfileSequenceDescription at cmsnamed.c:1017:16 in lcms2.h
// cmsFreeProfileSequenceDescription at cmsnamed.c:1017:16 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsUnregisterPluginsTHR at cmsplugin.c:780:16 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsContext createDummyContext() {
    // Create a dummy context for testing
    return cmsCreateContext(NULL, NULL);
}

static void freeDummyContext(cmsContext ctx) {
    // Free the dummy context
    cmsDeleteContext(ctx);
}

int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsContext context = createDummyContext();
    if (!context) return 0;

    cmsUInt32Number numProfiles = Data[0] % 256; // Number of profiles should be between 0 and 255

    cmsSEQ* seq = cmsAllocProfileSequenceDescription(context, numProfiles);
    if (seq) {
        cmsSEQ* dupSeq = cmsDupProfileSequenceDescription(seq);
        if (dupSeq) {
            cmsFreeProfileSequenceDescription(dupSeq);
        }
        cmsFreeProfileSequenceDescription(seq);
    }

    void* mem = _cmsMalloc(context, Size);
    if (mem) {
        _cmsFree(context, mem);
    }

    cmsUnregisterPluginsTHR(context);

    freeDummyContext(context);
    return 0;
}