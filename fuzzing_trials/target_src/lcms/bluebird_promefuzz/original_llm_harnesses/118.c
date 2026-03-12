// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsStageAllocPlaceholder at cmslut.c:31:21 in lcms2_plugin.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageType at cmslut.c:1228:29 in lcms2.h
// cmsStageData at cmslut.c:1233:17 in lcms2.h
// cmsStageDup at cmslut.c:1250:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsStage* DummyStageEvalFn(cmsFloat32Number* In, cmsFloat32Number* Out, const void* Data) {
    return NULL;
}

static void* DummyStageDupElemFn(const void* Data) {
    return NULL;
}

static void DummyStageFreeElemFn(void* Data) {
}

int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2 + sizeof(cmsStageSignature)) {
        return 0;
    }

    cmsContext context = NULL;
    cmsStageSignature type = *(cmsStageSignature*)Data;
    cmsUInt32Number inputChannels = *(cmsUInt32Number*)(Data + sizeof(cmsStageSignature));
    cmsUInt32Number outputChannels = *(cmsUInt32Number*)(Data + sizeof(cmsStageSignature) + sizeof(cmsUInt32Number));
    void* stageData = NULL;

    cmsStage* stage = _cmsStageAllocPlaceholder(
        context,
        type,
        inputChannels,
        outputChannels,
        DummyStageEvalFn,
        DummyStageDupElemFn,
        DummyStageFreeElemFn,
        stageData
    );

    if (stage) {
        cmsStage* identityStage = cmsStageAllocIdentity(context, inputChannels);
        if (identityStage) {
            cmsStage* nextStage = cmsStageNext(identityStage);
            cmsStageSignature stageType = cmsStageType(identityStage);
            void* data = cmsStageData(identityStage);

            cmsStage* duplicatedStage = cmsStageDup(identityStage);

            cmsStageFree(identityStage);
            cmsStageFree(duplicatedStage);
        }
        cmsStageFree(stage);
    }

    return 0;
}