#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize aom_image_t pointer
    aom_image_t *img = nullptr;

    // Allocate memory for aom_image_t structure
    img = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (img == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize the aom_image_t structure with some non-NULL values
    img->fmt = AOM_IMG_FMT_I420; // Set a valid image format
    img->w = 640;               // Set a width
    img->h = 480;               // Set a height
    img->d_w = 640;             // Set a display width
    img->d_h = 480;             // Set a display height
    img->x_chroma_shift = 1;    // Set chroma shift
    img->y_chroma_shift = 1;    // Set chroma shift
    img->planes[0] = (unsigned char *)data; // Assign data to the first plane
    img->stride[0] = 640;       // Set stride for the first plane

    // Call the function-under-test
    aom_img_free(img);

    // Free the allocated memory for the structure itself
    free(img);

    return 0;
}