#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int aom_img_plane_width(const aom_image_t *, int);

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a valid aom_image_t structure
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Initialize aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420;  // Set a valid image format
    img.d_w = 640;               // Set a width
    img.d_h = 480;               // Set a height
    img.stride[0] = 640;         // Set a stride for the Y plane
    img.stride[1] = 320;         // Set a stride for the U plane
    img.stride[2] = 320;         // Set a stride for the V plane

    // Use the first byte of data as the plane index
    int plane_index = data[0] % 3; // Ensure the plane index is within valid range

    // Call the function-under-test
    int width = aom_img_plane_width(&img, plane_index);

    // Use the result in some way (e.g., print, log, or further processing)
    // Here, we simply return 0 as the function's result doesn't affect fuzzing
    (void)width; // Suppress unused variable warning

    return 0;
}