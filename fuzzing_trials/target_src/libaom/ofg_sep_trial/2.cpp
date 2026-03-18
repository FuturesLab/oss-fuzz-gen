#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_encoder.h>
    #include <aom/aom_decoder.h>
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Initialize aom_metadata_t structure
    aom_metadata_t metadata;
    metadata.payload = const_cast<uint8_t*>(data); // Cast data to non-const
    metadata.sz = size;
    metadata.type = AOM_FRAME_IS_KEY; // Assign a valid type

    // Call the function-under-test
    aom_img_metadata_free(&metadata);

    return 0;
}