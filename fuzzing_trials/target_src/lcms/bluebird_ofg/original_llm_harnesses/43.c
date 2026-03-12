#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Initialize the cmsPipeline structure
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3);
    if (pipeline == NULL) {
        return 0;
    }

    // Create a cmsStage
    cmsToneCurve* toneCurves[3];
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildTabulatedToneCurve16(NULL, 2, (const uint16_t[]){0, 65535});
        if (toneCurves[i] == NULL) {
            for (int j = 0; j < i; j++) {
                cmsFreeToneCurve(toneCurves[j]);
            }
            cmsPipelineFree(pipeline);
            return 0;
        }
    }

    cmsStage *stage = cmsStageAllocToneCurves(NULL, 3, toneCurves);
    if (stage == NULL) {
        for (int i = 0; i < 3; i++) {
            cmsFreeToneCurve(toneCurves[i]);
        }
        cmsPipelineFree(pipeline);
        return 0;
    }

    // Insert the stage at the beginning of the pipeline
    cmsBool result = cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage);

    // Clean up
    cmsPipelineFree(pipeline);
    for (int i = 0; i < 3; i++) {
        cmsFreeToneCurve(toneCurves[i]);
    }
    
    return 0;
}