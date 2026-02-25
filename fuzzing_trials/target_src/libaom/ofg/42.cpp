#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_image.h>

extern "C" {
    int aom_img_set_rect(aom_image_t *img, unsigned int x, unsigned int y,
                         unsigned int width, unsigned int height,
                         unsigned int color);
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Initialize variables
    aom_image_t img;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int color = 0;

    // Ensure size is sufficient to use for parameters
    if (size < 5) {
        return 0; // Not enough data to proceed
    }

    // Initialize the aom_image_t structure
    aom_img_alloc(&img, AOM_IMG_FMT_I420, 640, 480, 1);

    // Set parameters using data from the input
    x = data[0] % img.d_w; // Ensure x is within image width
    y = data[1] % img.d_h; // Ensure y is within image height
    width = data[2] % (img.d_w - x); // Ensure width does not exceed bounds
    height = data[3] % (img.d_h - y); // Ensure height does not exceed bounds
    color = data[4]; // Use the 5th byte for color

    // Call the function under test
    int result = aom_img_set_rect(&img, x, y, width, height, color);

    // Clean up
    aom_img_free(&img);

    return result;
}