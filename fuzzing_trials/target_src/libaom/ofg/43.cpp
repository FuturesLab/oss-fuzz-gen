#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" {
    const aom_metadata_t * aom_img_get_metadata(const aom_image_t *, size_t);
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create and initialize an aom_image_t structure
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t));

    // Set some fields in aom_image_t to non-null values
    img.fmt = AOM_IMG_FMT_I420;
    img.w = 640;
    img.h = 480;
    img.d_w = 640;
    img.d_h = 480;
    img.bps = 12;
    img.stride[0] = 640;
    img.stride[1] = 320;
    img.stride[2] = 320;

    // Allocate memory for the image planes
    img.planes[0] = (uint8_t *)malloc(img.h * img.stride[0]);
    img.planes[1] = (uint8_t *)malloc(img.h / 2 * img.stride[1]);
    img.planes[2] = (uint8_t *)malloc(img.h / 2 * img.stride[2]);

    if (!img.planes[0] || !img.planes[1] || !img.planes[2]) {
        free(img.planes[0]);
        free(img.planes[1]);
        free(img.planes[2]);
        return 0;
    }

    // Use the data as metadata size
    size_t metadata_size = size - sizeof(aom_image_t);

    // Call the function-under-test
    const aom_metadata_t *metadata = aom_img_get_metadata(&img, metadata_size);

    // Free allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    // Return 0 indicating no crash
    return 0;
}