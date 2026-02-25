#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_image.h>

extern "C" {
    int aom_img_plane_height(const aom_image_t *, int);
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Initialize an aom_image_t structure
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t)); // Zero out the structure

    // Fill the aom_image_t structure with test data
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.w = 640;                // Example width
    img.h = 480;                // Example height
    img.stride[0] = 640;        // Example stride for Y plane
    img.stride[1] = 320;        // Example stride for U plane
    img.stride[2] = 320;        // Example stride for V plane

    // We can use the first byte of the input data to determine the plane index
    int plane_index = data[0] % 3; // Ensure the plane index is within bounds (0, 1, 2)

    // Call the function under test
    int height = aom_img_plane_height(&img, plane_index);

    // For fuzzing, we do not need to check the result, but we can use it if needed
    (void)height; // Avoid unused variable warning

    return 0;
}