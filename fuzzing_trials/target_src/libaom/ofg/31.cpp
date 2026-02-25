#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming the definition of aom_metadata_t is provided in the relevant AOM header file
extern "C" {
    #include "aom/aom_image.h" // Include the AOM header where aom_metadata_t is defined
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure size is non-zero and does not exceed a reasonable limit
    if (size == 0 || size > 1024) {
        return 0; // Invalid input size
    }

    // Allocate memory for aom_metadata_t
    aom_metadata_t *metadata = (aom_metadata_t *)malloc(sizeof(aom_metadata_t));
    if (metadata == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the metadata structure with data from the input
    // Here we assume aom_metadata_t has a field that can be initialized with the input data
    // This is a hypothetical example; the actual initialization will depend on the structure's definition.
    memcpy(metadata, data, size < sizeof(aom_metadata_t) ? size : sizeof(aom_metadata_t));

    // Call the function under test
    aom_img_metadata_free(metadata);

    // Free the allocated memory (if not handled inside aom_img_metadata_free)
    free(metadata);

    return 0;
}