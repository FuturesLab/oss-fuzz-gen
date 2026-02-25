#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_image.h>

extern "C" {

void aom_img_remove_metadata(aom_image_t *img);

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure the size is within a reasonable limit for an image
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Allocate memory for aom_image_t
    aom_image_t *img = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (img == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the aom_image_t structure
    memset(img, 0, sizeof(aom_image_t));
    
    // Populate the aom_image_t structure with data
    img->fmt = AOM_IMG_FMT_I420; // Example format
    img->d_w = 640; // Example width
    img->d_h = 480; // Example height
    img->bit_depth = 8; // Example bit depth
    img->planes[0] = (uint8_t *)malloc(img->d_w * img->d_h); // Y plane
    img->planes[1] = (uint8_t *)malloc((img->d_w / 2) * (img->d_h / 2)); // U plane
    img->planes[2] = (uint8_t *)malloc((img->d_w / 2) * (img->d_h / 2)); // V plane

    // Check if memory allocation for planes was successful
    if (img->planes[0] == NULL || img->planes[1] == NULL || img->planes[2] == NULL) {
        free(img->planes[0]);
        free(img->planes[1]);
        free(img->planes[2]);
        free(img);
        return 0; // Memory allocation failed
    }

    // Fill the image planes with data from the input
    memcpy(img->planes[0], data, img->d_w * img->d_h); // Copy Y plane data
    memcpy(img->planes[1], data + img->d_w * img->d_h, (img->d_w / 2) * (img->d_h / 2)); // Copy U plane data
    memcpy(img->planes[2], data + img->d_w * img->d_h + (img->d_w / 2) * (img->d_h / 2), (img->d_w / 2) * (img->d_h / 2)); // Copy V plane data

    // Call the function under test
    aom_img_remove_metadata(img);

    // Free allocated memory
    free(img->planes[0]);
    free(img->planes[1]);
    free(img->planes[2]);
    free(img);

    return 0;
}

}