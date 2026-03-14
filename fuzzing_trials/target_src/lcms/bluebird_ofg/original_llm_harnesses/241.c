#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    // Ensure there is enough data to use
    if (size < 4) {
        return 0;
    }

    // Initialize the variables
    cmsPipeline *pipeline = cmsPipelineAlloc(NULL, 3, 3); // Assuming 3 input and 3 output channels
    if (pipeline == NULL) {
        return 0; // If allocation fails, return immediately
    }

    // Use the first byte of data to determine the boolean flag
    cmsBool flag = (cmsBool)(data[0] % 2);

    // Use additional data to create a simple LUT (Look-Up Table)
    cmsStage *stage = cmsStageAllocToneCurves(NULL, 3, (cmsToneCurve*[]){ 
        cmsBuildGamma(NULL, data[1] / 255.0 + 1.0), 
        cmsBuildGamma(NULL, data[2] / 255.0 + 1.0), 
        cmsBuildGamma(NULL, data[3] / 255.0 + 1.0) 
    });

    if (stage != NULL) {
        cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage);
    }

    // Call the function-under-test
    cmsBool result = cmsPipelineSetSaveAs8bitsFlag(pipeline, flag);

    // Clean up
    cmsPipelineFree(pipeline);

    return 0;
}