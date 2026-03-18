#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "aom/aom_image.h"  // Assuming this is the correct header for aom_metadata_t

extern "C" {
    #include "aom/aom_image.h"
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Allocate memory for aom_metadata_t
    aom_metadata_t *metadata = (aom_metadata_t *)malloc(sizeof(aom_metadata_t));
    if (metadata == NULL) {
        return 0;  // Return if memory allocation fails
    }

    // Initialize the metadata with some data
    metadata->payload = (uint8_t *)malloc(size);
    if (metadata->payload == NULL) {
        free(metadata);
        return 0;  // Return if memory allocation fails
    }
    memcpy(metadata->payload, data, size);
    metadata->sz = size;

    // Call the function under test
    aom_img_metadata_free(metadata);

    // Free the allocated memory for metadata
    free(metadata->payload);
    free(metadata);

    return 0;
}