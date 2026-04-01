#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_318(const uint8_t *data, size_t size) {
    cmsPipeline *pipeline = NULL;

    // Initialize a cmsPipeline with a non-NULL value
    pipeline = cmsPipelineAlloc(NULL, 3, 3);
    if (pipeline == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsPipelineFree(pipeline);

    return 0;
}