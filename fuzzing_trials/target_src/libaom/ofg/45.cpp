extern "C" {
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize an aom_image_t structure
    aom_image_t img;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Use a common format
    unsigned int d_w = 640; // Set a default width
    unsigned int d_h = 480; // Set a default height
    unsigned int stride_align = 1;

    // Initialize the image
    if (!aom_img_alloc(&img, fmt, d_w, d_h, stride_align)) {
        return 0; // Allocation failed
    }

    // Ensure the size is not zero to avoid division by zero
    if (size == 0) {
        size = 1;
    }

    // Call the function-under-test
    const aom_metadata_t *metadata = aom_img_get_metadata(&img, size);

    // Clean up
    aom_img_free(&img);

    return 0;
}