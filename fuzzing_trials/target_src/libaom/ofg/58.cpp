#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to initialize an aom_image_t structure
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create and initialize an aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = 640; // Displayed width
    img.d_h = 480; // Displayed height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bit_depth = 8;
    img.img_data = (uint8_t *)data; // Use the input data as image data
    img.img_data_owner = 0;
    img.self_allocd = 0;
    img.fb_priv = nullptr;

    // Call the function under test
    aom_img_remove_metadata(&img);

    return 0;
}