#include <stdint.h>
#include <stddef.h>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Initialize variables
    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Using a valid image format
    unsigned int width = 640;  // Default width
    unsigned int height = 480; // Default height
    unsigned int align = 1;    // Default alignment

    // Adjust width, height, and alignment based on input data if size permits
    if (size >= 12) {
        width = (unsigned int)data[0] + ((unsigned int)data[1] << 8);
        height = (unsigned int)data[2] + ((unsigned int)data[3] << 8);
        align = (unsigned int)data[4] % 32 + 1; // Ensure alignment is non-zero
        fmt = (aom_img_fmt_t)(data[5] % 4); // Assuming 4 different formats for simplicity
    }

    // Call the function-under-test
    img = aom_img_alloc(img, fmt, width, height, align);

    // Clean up
    if (img != nullptr) {
        aom_img_free(img);
    }

    return 0;
}