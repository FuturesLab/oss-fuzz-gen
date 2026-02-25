#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_image.h>
#include <aom/aom_image.h>

extern "C" {

aom_image_t *aom_img_wrap(aom_image_t *img, aom_img_fmt_t fmt, unsigned int width, unsigned int height, unsigned int stride, unsigned char *data);

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the size is valid for the image data
    if (size < 1) {
        return 0;
    }

    // Initialize parameters for aom_img_wrap
    aom_image_t img;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Example format
    unsigned int width = 640; // Example width
    unsigned int height = 480; // Example height
    unsigned int stride = width; // Example stride
    unsigned char *image_data = (unsigned char *)malloc(size);

    // Ensure image_data is not NULL
    if (image_data == NULL) {
        return 0;
    }

    // Copy data into image_data to avoid NULL usage
    memcpy(image_data, data, size < (width * height * 3 / 2) ? size : (width * height * 3 / 2));

    // Call the function under test
    aom_image_t *result = aom_img_wrap(&img, fmt, width, height, stride, image_data);

    // Free allocated memory
    free(image_data);

    // Result can be checked here if needed
    if (result != NULL) {
        // Do something with the result if necessary
    }

    return 0;
}
}