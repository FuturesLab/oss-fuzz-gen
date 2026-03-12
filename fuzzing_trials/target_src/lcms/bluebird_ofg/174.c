#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    cmsPipeline *pipeline = NULL;
    cmsStage *stage = NULL;

    // Initialize the pipeline with some stages if possible
    if (size > 0) {
        pipeline = cmsPipelineAlloc(NULL, 3, 3); // Example: 3 input channels, 3 output channels

        if (pipeline != NULL) {
            cmsStage *stage1 = cmsStageAllocIdentity(NULL, 3);
            cmsStage *stage2 = cmsStageAllocIdentity(NULL, 3);

            if (stage1 != NULL && stage2 != NULL) {
                cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage1);
                cmsPipelineInsertStage(pipeline, cmsAT_END, stage2);

                // Call the function-under-test only if the pipeline has stages
                stage = cmsPipelineGetPtrToFirstStage(pipeline);
                if (stage != NULL) {
                    // Prepare some input data for the pipeline
                    uint16_t input[3] = {0};
                    uint16_t output[3] = {0};

                    // Use the first few bytes of the input data to populate the input array
                    if (size >= 6) {
                        input[0] = (data[0] << 8) | data[1];
                        input[1] = (data[2] << 8) | data[3];
                        input[2] = (data[4] << 8) | data[5];
                    }

                    // Evaluate the pipeline with the input data
                    cmsPipelineEval16(input, output, pipeline);
                }
            } else {
                // Free allocated stages if they were allocated
                if (stage1 != NULL) cmsStageFree(stage1);
                if (stage2 != NULL) cmsStageFree(stage2);
            }
        }
    }

    // Clean up
    if (pipeline != NULL) {
        cmsPipelineFree(pipeline);
    }

    return 0;
}