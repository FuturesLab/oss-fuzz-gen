#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>

extern "C" {
    // Include the necessary library headers
    #include <aom/aom_codec.h>
    #include <aom/aom_image.h>
}

// Fuzzing harness for the function aom_img_metadata_free
extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Create an aom_metadata_t object
    aom_metadata_t metadata;
    metadata.payload = nullptr;
    metadata.sz = 0;

    // Ensure size is not zero to avoid division by zero
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the payload based on the input size
    metadata.payload = static_cast<uint8_t*>(malloc(size));
    if (metadata.payload == nullptr) {
        return 0;
    }

    // Copy the input data to the payload
    memcpy(metadata.payload, data, size);
    metadata.sz = size;

    // Call the function under test
    aom_img_metadata_free(&metadata);

    // Free the allocated memory if it wasn't freed by the function
    if (metadata.payload != nullptr) {
        free(metadata.payload);
    }

    return 0;
}