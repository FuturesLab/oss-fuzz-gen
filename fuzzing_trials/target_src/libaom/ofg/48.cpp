#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Using a common format
    unsigned int d_w = 640; // Default width
    unsigned int d_h = 480; // Default height
    unsigned int stride_align = 32; // Common stride alignment
    unsigned int border = 32; // Common border size
    unsigned int img_flags = 0; // No specific flags

    // Call the function-under-test
    aom_image_t *result = aom_img_alloc_with_border(img, fmt, d_w, d_h, stride_align, border, img_flags);

    // Check if the result is not null and free the image if allocated
    if (result != nullptr) {
        aom_img_free(result);
    }

    return 0;
}