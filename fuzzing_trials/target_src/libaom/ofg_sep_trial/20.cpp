#include <stdint.h>
#include <stddef.h>
#include <aom/aom_image.h>

extern "C" {
    int aom_img_plane_height(const aom_image_t *img, int plane);
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create an aom_image_t structure
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Cast the input data to aom_image_t structure
    const aom_image_t *img = reinterpret_cast<const aom_image_t *>(data);

    // Define a non-negative plane index
    int plane = 0; // You can try different values like 0, 1, 2, etc.

    // Call the function under test
    int height = aom_img_plane_height(img, plane);

    // Use the result in some way to avoid compiler optimizations
    (void)height;

    return 0;
}