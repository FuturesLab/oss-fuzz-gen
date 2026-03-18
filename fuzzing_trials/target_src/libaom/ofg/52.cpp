#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Using a common format for initialization
    unsigned int d_w = 640; // Default width
    unsigned int d_h = 480; // Default height
    unsigned int align = 1; // Default alignment
    unsigned int border = 32; // Default border
    unsigned int stride_align = 1; // Default stride alignment

    // Call the function-under-test
    aom_image_t *result = aom_img_alloc_with_border(img, fmt, d_w, d_h, align, border, stride_align);

    // Free the allocated image if not null
    if (result != nullptr) {
        aom_img_free(result);
    }

    return 0;
}