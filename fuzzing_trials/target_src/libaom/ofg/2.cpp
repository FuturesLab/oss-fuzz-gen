#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    // Include the necessary C headers and functions
    #include <aom/aom_image.h>
    #include <aom/aom_codec.h>  // Include the codec header for metadata-related definitions
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for creating aom_metadata_t
    if (size < sizeof(aom_metadata_t)) {
        return 0;
    }

    // Allocate memory for aom_metadata_t
    aom_metadata_t *metadata = (aom_metadata_t *)malloc(sizeof(aom_metadata_t));
    if (metadata == NULL) {
        return 0;
    }

    // Initialize the metadata fields with non-null values
    metadata->payload = (uint8_t *)data;
    metadata->sz = size;  // Corrected member name from 'payload_size' to 'sz'

    // Call the function-under-test
    aom_img_metadata_free(metadata);

    // Free the allocated memory
    free(metadata);

    return 0;
}