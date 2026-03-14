#include <stdint.h>
#include <stddef.h>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t img;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int w = 1;
    unsigned int h = 1;
    unsigned int border = 0;

    // Ensure the data size is large enough to extract meaningful values
    if (size >= 5 * sizeof(unsigned int)) {
        // Extract values from the data
        x = ((unsigned int *)data)[0];
        y = ((unsigned int *)data)[1];
        w = ((unsigned int *)data)[2];
        h = ((unsigned int *)data)[3];
        border = ((unsigned int *)data)[4];
    }

    // Initialize the aom_image_t structure
    aom_img_alloc(&img, AOM_IMG_FMT_I420, 640, 480, 1);

    // Call the function under test
    aom_img_set_rect(&img, x, y, w, h, border);

    // Free the allocated image
    aom_img_free(&img);

    return 0;
}