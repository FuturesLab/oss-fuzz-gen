#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" {

const aom_metadata_t * aom_img_get_metadata(const aom_image_t *, size_t);

}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure the size is valid for creating an aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create and initialize an aom_image_t
    aom_image_t img;
    std::memset(&img, 0, sizeof(aom_image_t)); // Zero out the structure

    // Fill in the aom_image_t structure with data from the input
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.d_w = 640; // Example width (changed from img.width)
    img.d_h = 480; // Example height (changed from img.height)
    img.stride[0] = img.d_w;
    img.stride[1] = img.d_w / 2;
    img.stride[2] = img.d_w / 2;

    // Allocate memory for the image data
    img.planes[0] = (uint8_t *)malloc(img.stride[0] * img.d_h);
    img.planes[1] = (uint8_t *)malloc(img.stride[1] * (img.d_h / 2));
    img.planes[2] = (uint8_t *)malloc(img.stride[2] * (img.d_h / 2));

    // Check for successful memory allocation
    if (!img.planes[0] || !img.planes[1] || !img.planes[2]) {
        free(img.planes[0]);
        free(img.planes[1]);
        free(img.planes[2]);
        return 0;
    }

    // Fill the image data with the input data
    size_t data_size = size < (img.stride[0] * img.d_h) ? size : (img.stride[0] * img.d_h);
    std::memcpy(img.planes[0], data, data_size);

    // Call the function under test
    const aom_metadata_t *metadata = aom_img_get_metadata(&img, size);

    // Clean up allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}