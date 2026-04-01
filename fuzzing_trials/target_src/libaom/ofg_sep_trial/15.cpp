#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <aom/aom_image.h>
    #include <aom/aom_codec.h>
    #include <aom/aom.h>

    // Function signature from the library
    aom_metadata_t * aom_img_metadata_alloc(uint32_t type, const uint8_t *data, size_t sz, aom_metadata_insert_flags_t flags);
    // Assume there's a function to free the metadata
    void aom_img_metadata_free(aom_metadata_t *metadata);
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Define and initialize parameters for aom_img_metadata_alloc
    uint32_t type = 1; // Example type, can be varied
    const uint8_t *metadata_data = data; // Use the input data as metadata
    size_t metadata_size = size; // Use the input size as metadata size
    aom_metadata_insert_flags_t flags = static_cast<aom_metadata_insert_flags_t>(0); // Use 0 if AOM_MIF_NONE is not available

    // Call the function-under-test
    aom_metadata_t *metadata = aom_img_metadata_alloc(type, metadata_data, metadata_size, flags);

    // Clean up if necessary
    if (metadata != NULL) {
        // Free the allocated metadata
        aom_img_metadata_free(metadata);
    }

    return 0;
}