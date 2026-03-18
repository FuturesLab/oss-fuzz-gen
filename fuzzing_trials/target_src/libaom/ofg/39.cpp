#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our parameters
    if (size < 12) {
        return 0;
    }

    // Initialize parameters for aom_img_wrap
    aom_image_t img;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(data[0] % 4); // Limiting to a few formats
    unsigned int d_w = static_cast<unsigned int>(data[1]) + 1; // Avoid zero width
    unsigned int d_h = static_cast<unsigned int>(data[2]) + 1; // Avoid zero height
    unsigned int stride_align = static_cast<unsigned int>(data[3]) + 1; // Avoid zero stride alignment
    unsigned char *img_data = const_cast<unsigned char*>(data + 4);

    // Call the function-under-test
    aom_image_t *result = aom_img_wrap(&img, fmt, d_w, d_h, stride_align, img_data);

    // Optionally, perform some checks or operations on the result
    if (result != nullptr) {
        // Example operation: check if the image format matches
        if (result->fmt != fmt) {
            return 1;
        }
    }

    return 0;
}