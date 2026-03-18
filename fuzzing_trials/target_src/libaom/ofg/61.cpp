#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize the aom_image_t structure
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Allocate memory for the aom_image_t structure
    aom_image_t *img = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (img == NULL) {
        return 0;
    }

    // Initialize the aom_image_t structure with some data
    // Copy data from the input to the img structure
    memcpy(img, data, sizeof(aom_image_t));

    // Call the function-under-test
    aom_img_remove_metadata(img);

    // Clean up
    free(img);

    return 0;
}