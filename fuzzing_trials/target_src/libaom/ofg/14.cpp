#include <aom/aom_image.h>
#include <stdlib.h>
#include <stdint.h>

extern "C" {
    void aom_img_remove_metadata(aom_image_t *);
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure size is large enough to create a valid aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Allocate memory for aom_image_t
    aom_image_t *image = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (image == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the aom_image_t structure with data
    // Assuming the first part of data can be used to initialize the image
    // This is a simplified initialization. In a real scenario, you would
    // need to set up the image properties correctly based on your use case.
    image->fmt = AOM_IMG_FMT_I420; // Example format
    image->d_w = 640;               // Example width
    image->d_h = 480;               // Example height
    image->planes[0] = (uint8_t *)data; // Use input data for the Y plane
    image->planes[1] = image->planes[0] + (640 * 480); // Example for U plane
    image->planes[2] = image->planes[1] + (320 * 240); // Example for V plane

    // Call the function-under-test
    aom_img_remove_metadata(image);

    // Clean up
    free(image);

    return 0;
}