#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include "aom/aom_image.h"  // Assuming this header contains the function declaration

extern "C" {
    aom_metadata_t * aom_img_metadata_alloc(uint32_t type, const uint8_t *data, size_t data_size, aom_metadata_insert_flags_t flags);
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for extracting parameters
    if (size < sizeof(uint32_t) + sizeof(aom_metadata_insert_flags_t)) {
        return 0;
    }

    // Extract the uint32_t parameter from the data
    uint32_t type = *(reinterpret_cast<const uint32_t*>(data));
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Extract the aom_metadata_insert_flags_t parameter from the data
    aom_metadata_insert_flags_t flags = *(reinterpret_cast<const aom_metadata_insert_flags_t*>(data));
    data += sizeof(aom_metadata_insert_flags_t);
    size -= sizeof(aom_metadata_insert_flags_t);

    // Remaining data is used as the metadata content
    const uint8_t *metadata_content = data;
    size_t metadata_size = size;

    // Call the function under test
    aom_metadata_t *metadata = aom_img_metadata_alloc(type, metadata_content, metadata_size, flags);

    // Clean up if necessary (assuming aom_img_metadata_free is available for cleanup)
    if (metadata != nullptr) {
        // Assuming a function like this exists for cleanup
        // aom_img_metadata_free(metadata);
    }

    return 0;
}