#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_387(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);
    
    // Create a cmsPipeline object
    cmsPipeline *pipeline = cmsPipelineAlloc(contextID, 3, 3);
    
    if (pipeline == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }
    
    // Call the function-under-test
    cmsUInt32Number stageCount = cmsPipelineStageCount(pipeline);
    
    // Clean up
    cmsPipelineFree(pipeline);
    cmsDeleteContext(contextID);
    
    return 0;
}