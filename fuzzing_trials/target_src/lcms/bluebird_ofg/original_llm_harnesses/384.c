#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include stdlib.h for malloc and free
#include <string.h>  // Include string.h for memcpy
#include <lcms2.h>

// Define a reasonable size for the cmsStage object
#define CMS_STAGE_SIZE 128  // Assumed size, adjust according to actual library usage

int LLVMFuzzerTestOneInput_384(const uint8_t *data, size_t size) {
    cmsStage *stage = NULL;
    cmsStage *nextStage = NULL;

    // Ensure that the size is sufficient to create a cmsStage object
    if (size >= CMS_STAGE_SIZE) {
        // Allocate memory for the cmsStage object
        stage = (cmsStage *)malloc(CMS_STAGE_SIZE);
        if (stage == NULL) {
            return 0;
        }

        // Initialize the cmsStage object with data
        memcpy(stage, data, CMS_STAGE_SIZE);

        // Call the function-under-test
        nextStage = cmsStageNext(stage);

        // Free the allocated memory
        free(stage);
    }

    return 0;
}