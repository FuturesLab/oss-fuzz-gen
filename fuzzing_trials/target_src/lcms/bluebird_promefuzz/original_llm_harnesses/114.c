// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsStageAllocMatrix at cmslut.c:379:22 in lcms2.h
// cmsGetStageContextID at cmslut.c:1238:22 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// _cmsStageAllocPlaceholder at cmslut.c:31:21 in lcms2_plugin.h
// cmsGetStageContextID at cmslut.c:1238:22 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsGetStageContextID at cmslut.c:1238:22 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocToneCurves at cmslut.c:248:21 in lcms2.h
// cmsGetStageContextID at cmslut.c:1238:22 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2_plugin.h>
#include <lcms2.h>

static cmsFloat64Number dummyMatrix[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
};

static cmsFloat64Number dummyOffset[3] = {0.0, 0.0, 0.0};

static cmsFloat64Number dummyEvalFunction(cmsInt32Number Type, const cmsFloat64Number Params[10], cmsFloat64Number R) {
    return R;
}

static void dummyFreeFunction(void* Data) {
    // Dummy free function
}

static void* dummyDupFunction(void* Data) {
    return Data;
}

int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2) return 0;

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) return 0;

    // Fuzz cmsStageAllocMatrix
    cmsUInt32Number rows = *(cmsUInt32Number*)Data % 3; // Ensure rows are within bounds of dummyMatrix
    cmsUInt32Number cols = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number)) % 3; // Ensure cols are within bounds

    cmsStage* stageMatrix = cmsStageAllocMatrix(context, rows, cols, (const cmsFloat64Number*)dummyMatrix, dummyOffset);
    if (stageMatrix) {
        cmsGetStageContextID(stageMatrix);
        cmsStageNext(stageMatrix);
        cmsStageFree(stageMatrix);
    }

    // Fuzz _cmsStageAllocPlaceholder
    cmsStage* stagePlaceholder = _cmsStageAllocPlaceholder(context, 0, rows, cols,
                                                           (void*)dummyEvalFunction,
                                                           (void*)dummyDupFunction,
                                                           (void*)dummyFreeFunction,
                                                           NULL);
    if (stagePlaceholder) {
        cmsGetStageContextID(stagePlaceholder);
        cmsStageNext(stagePlaceholder);
        cmsStageFree(stagePlaceholder);
    }

    // Fuzz cmsStageAllocIdentity
    cmsStage* stageIdentity = cmsStageAllocIdentity(context, rows);
    if (stageIdentity) {
        cmsGetStageContextID(stageIdentity);
        cmsStageNext(stageIdentity);
        cmsStageFree(stageIdentity);
    }

    // Fuzz cmsStageAllocToneCurves
    cmsToneCurve* curves[3] = {NULL, NULL, NULL};
    cmsStage* stageToneCurves = cmsStageAllocToneCurves(context, 3, curves);
    if (stageToneCurves) {
        cmsGetStageContextID(stageToneCurves);
        cmsStageNext(stageToneCurves);
        cmsStageFree(stageToneCurves);
    }

    cmsDeleteContext(context);
    return 0;
}