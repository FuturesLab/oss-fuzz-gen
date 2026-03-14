#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for std::memcpy

extern "C" {
    #include <aom/aom_image.h> // Wrap C library includes in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create an aom_image_t structure
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create an aom_image_t structure and initialize it with the input data
    aom_image_t img;
    std::memcpy(&img, data, sizeof(aom_image_t));

    // Call the function-under-test
    size_t num_metadata = aom_img_num_metadata(&img);

    // Use the result in some way to avoid compiler optimizations
    volatile size_t result = num_metadata;
    (void)result;

    return 0;
}