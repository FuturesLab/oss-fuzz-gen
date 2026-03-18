#include <stdint.h>
#include <stddef.h>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    aom_image_t *img = nullptr; // Pointer to an aom_image_t structure
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Image format (using a valid format)
    unsigned int d_w = 640; // Image width
    unsigned int d_h = 480; // Image height
    unsigned int stride_align = 16; // Stride alignment
    unsigned int border = 32; // Border size
    unsigned int init_flags = 0; // Initialization flags

    // Call the function-under-test
    aom_image_t *result = aom_img_alloc_with_border(img, fmt, d_w, d_h, stride_align, border, init_flags);

    // Free the allocated image if it was successfully created
    if (result != nullptr) {
        aom_img_free(result);
    }

    return 0;
}