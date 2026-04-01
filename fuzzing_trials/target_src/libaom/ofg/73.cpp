#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>

extern "C" {
    // Function prototype for the function-under-test
    void aom_img_flip(aom_image_t *);
}

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Declare and initialize an aom_image_t structure
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t)); // Initialize all fields to zero

    // Set up the image parameters with non-NULL values
    img.fmt = AOM_IMG_FMT_I420; // Set a valid image format
    img.w = 640; // Set a valid width
    img.h = 480; // Set a valid height
    img.d_w = 640; // Set display width
    img.d_h = 480; // Set display height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bps = 12; // Bits per sample

    // Allocate memory for the image data planes
    img.planes[0] = (uint8_t *)malloc(img.w * img.h); // Y plane
    img.planes[1] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // U plane
    img.planes[2] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // V plane

    // Ensure the allocated memory is not NULL
    if (img.planes[0] == NULL || img.planes[1] == NULL || img.planes[2] == NULL) {
        free(img.planes[0]);
        free(img.planes[1]);
        free(img.planes[2]);
        return 0;
    }

    // Call the function-under-test
    aom_img_flip(&img);

    // Free the allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}