#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_411(const uint8_t *data, size_t size) {
    cmsPipeline *pipeline = NULL;
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a dummy pipeline with at least one stage for testing
    if (context != NULL) {
        pipeline = cmsPipelineAlloc(context, 3, 3);
        if (pipeline != NULL) {
            cmsStage *stage = cmsStageAllocIdentity(context, 3);
            if (stage != NULL) {
                cmsPipelineInsertStage(pipeline, cmsAT_END, stage);
            }
        }
    }

    if (pipeline != NULL && size >= 3 * sizeof(cmsFloat32Number)) {
        // Prepare input data for the pipeline
        cmsFloat32Number input[3];
        for (int i = 0; i < 3; ++i) {
            input[i] = ((cmsFloat32Number*)data)[i];
        }

        // Prepare output buffer
        cmsFloat32Number output[3];

        // Call the function under test with the input data
        cmsPipelineEvalFloat(input, output, pipeline);
        
        // Use the output variable to prevent compiler optimization
        (void)output;

        // Clean up
        cmsPipelineFree(pipeline);
    }

    cmsDeleteContext(context);

    return 0;
}