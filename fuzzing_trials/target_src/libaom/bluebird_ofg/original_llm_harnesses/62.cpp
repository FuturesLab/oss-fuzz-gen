#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    void aom_img_remove_metadata(aom_image_t *img);
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Initialize an aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Set a valid format
    img.w = 640;                // Set a width
    img.h = 480;                // Set a height
    img.d_w = 640;              // Set display width
    img.d_h = 480;              // Set display height
    img.x_chroma_shift = 1;     // Set chroma shift
    img.y_chroma_shift = 1;     // Set chroma shift
    img.planes[0] = (uint8_t *)data; // Use the input data as a plane
    img.stride[0] = 640;        // Set stride
    img.bps = 8;                // Bits per sample

    // Call the function under test
    aom_img_remove_metadata(&img);

    return 0;
}