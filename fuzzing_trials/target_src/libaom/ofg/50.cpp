#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize parameters for aom_img_alloc
    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // A commonly used format
    unsigned int d_w = 640; // Example width
    unsigned int d_h = 480; // Example height
    unsigned int align = 1; // Default alignment

    // Call the function under test
    aom_image_t *result = aom_img_alloc(img, fmt, d_w, d_h, align);

    // Clean up if the image was allocated
    if (result != nullptr) {
        aom_img_free(result);
    }

    return 0;
}