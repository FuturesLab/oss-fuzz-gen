#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include the necessary headers for the aom_metadata_t structure
    #include <aom/aom_image.h>
}

// Fuzzing harness for the aom_img_metadata_free function
extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to create a valid aom_metadata_t
    if (size < sizeof(aom_metadata_t)) {
        return 0;
    }

    // Allocate memory for aom_metadata_t
    aom_metadata_t *metadata = (aom_metadata_t *)malloc(sizeof(aom_metadata_t));
    if (metadata == NULL) {
        return 0; // Handle memory allocation failure
    }

    // Initialize the metadata structure with data from the input
    memcpy(metadata, data, sizeof(aom_metadata_t));

    // Call the function under test
    aom_img_metadata_free(metadata);

    // Free the allocated memory
    free(metadata);

    return 0;
}