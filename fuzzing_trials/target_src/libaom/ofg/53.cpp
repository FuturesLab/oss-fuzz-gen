#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < 20) {
        return 0;
    }

    // Initialize the parameters
    aom_image_t img;
    unsigned int x = static_cast<unsigned int>(data[0]);
    unsigned int y = static_cast<unsigned int>(data[1]);
    unsigned int w = static_cast<unsigned int>(data[2]);
    unsigned int h = static_cast<unsigned int>(data[3]);
    unsigned int stride = static_cast<unsigned int>(data[4]);

    // Initialize the aom_image_t structure
    aom_img_alloc(&img, AOM_IMG_FMT_I420, 640, 480, 1);

    // Call the function-under-test
    aom_img_set_rect(&img, x, y, w, h, stride);

    // Free the allocated image
    aom_img_free(&img);

    return 0;
}