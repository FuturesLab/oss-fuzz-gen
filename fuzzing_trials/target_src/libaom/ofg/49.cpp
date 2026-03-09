extern "C" {
#include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract parameters
    if (size < 5 * sizeof(unsigned int)) {
        return 0;
    }

    // Initialize parameters for aom_img_alloc_with_border
    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(data[0] % 10); // Assuming there are 10 possible formats
    unsigned int width = static_cast<unsigned int>(data[1] + 1);  // Ensure width is non-zero
    unsigned int height = static_cast<unsigned int>(data[2] + 1); // Ensure height is non-zero
    unsigned int border = static_cast<unsigned int>(data[3]);
    unsigned int stride_align = static_cast<unsigned int>(data[4]);
    unsigned int border_align = static_cast<unsigned int>(data[5]);

    // Call the function-under-test
    aom_image_t *result = aom_img_alloc_with_border(img, fmt, width, height, border, stride_align, border_align);

    // Free the allocated image if not null
    if (result != nullptr) {
        aom_img_free(result);
    }

    return 0;
}