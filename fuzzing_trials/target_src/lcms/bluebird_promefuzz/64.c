#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcms2.h"

static void fuzz_cmsStageAllocIdentity(cmsContext context, cmsUInt32Number nChannels) {
    cmsStage* stage = cmsStageAllocIdentity(context, nChannels);
    if (stage) {
        cmsStageFree(stage);
    }
}

static void fuzz_cmsStageNext(cmsStage* stage) {
    cmsStage* nextStage = cmsStageNext(stage);
    // No need to free nextStage as it is part of a linked list managed elsewhere
}

static void fuzz_cmsStageDup(cmsStage* stage) {
    cmsStage* dupStage = cmsStageDup(stage);
    if (dupStage) {
        cmsStageFree(dupStage);
    }
}

static void fuzz_cmsStageAllocCLutFloat(cmsContext context, cmsUInt32Number nGridPoints, cmsUInt32Number inputChan, cmsUInt32Number outputChan, const cmsFloat32Number* table, size_t tableSize) {
    // Calculate the required size for the table
    size_t requiredSize = nGridPoints * inputChan * outputChan * sizeof(cmsFloat32Number);

    // Ensure the table size is sufficient
    if (tableSize < requiredSize || nGridPoints == 0 || inputChan == 0 || outputChan == 0) {
        return;
    }

    cmsStage* clutStage = cmsStageAllocCLutFloat(context, nGridPoints, inputChan, outputChan, table);
    if (clutStage) {
        cmsStageFree(clutStage);
    }
}

static void fuzz_cmsStageData(cmsStage* stage) {
    void* data = cmsStageData(stage);
    // No need to free data as it is managed by the stage itself
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 4) {
        return 0;
    }

    cmsContext context = NULL;
    cmsUInt32Number nChannels = *(const cmsUInt32Number*)Data;
    cmsUInt32Number nGridPoints = *(const cmsUInt32Number*)(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number inputChan = *(const cmsUInt32Number*)(Data + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number outputChan = *(const cmsUInt32Number*)(Data + 3 * sizeof(cmsUInt32Number));
    const cmsFloat32Number* table = (const cmsFloat32Number*)(Data + 4 * sizeof(cmsUInt32Number));
    size_t tableSize = Size - 4 * sizeof(cmsUInt32Number);

    fuzz_cmsStageAllocIdentity(context, nChannels);

    cmsStage* stage = cmsStageAllocIdentity(context, nChannels);
    if (stage) {
        fuzz_cmsStageNext(stage);
        fuzz_cmsStageDup(stage);
        fuzz_cmsStageData(stage);
        cmsStageFree(stage);
    }

    fuzz_cmsStageAllocCLutFloat(context, nGridPoints, inputChan, outputChan, table, tableSize);

    return 0;
}