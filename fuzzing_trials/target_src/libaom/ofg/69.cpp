#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>

extern "C" {
    void aom_img_flip(aom_image_t *);
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Initialize an aom_image_t structure
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t));

    // Ensure the data size is sufficient for setting up the image
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Example initialization of aom_image_t fields
    img.fmt = AOM_IMG_FMT_I420; // Common format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = img.w;
    img.d_h = img.h;
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;

    // Allocate image data
    img.stride[0] = img.w;
    img.stride[1] = img.w / 2;
    img.stride[2] = img.w / 2;
    img.planes[0] = (uint8_t *)malloc(img.h * img.stride[0]);
    img.planes[1] = (uint8_t *)malloc((img.h / 2) * img.stride[1]);
    img.planes[2] = (uint8_t *)malloc((img.h / 2) * img.stride[2]);

    // Check if memory allocation was successful
    if (!img.planes[0] || !img.planes[1] || !img.planes[2]) {
        free(img.planes[0]);
        free(img.planes[1]);
        free(img.planes[2]);
        return 0;
    }

    // Fill the image planes with data from the input
    size_t plane_size = img.h * img.stride[0];
    memcpy(img.planes[0], data, plane_size < size ? plane_size : size);

    plane_size = (img.h / 2) * img.stride[1];
    memcpy(img.planes[1], data, plane_size < size ? plane_size : size);

    plane_size = (img.h / 2) * img.stride[2];
    memcpy(img.planes[2], data, plane_size < size ? plane_size : size);

    // Call the function under test
    aom_img_flip(&img);

    // Clean up allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}