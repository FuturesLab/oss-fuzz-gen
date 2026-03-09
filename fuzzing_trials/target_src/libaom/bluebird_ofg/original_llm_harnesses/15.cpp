#include <stdint.h>
#include <stddef.h>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    aom_image_t img;
    
    // Initialize the aom_image_t structure with non-NULL values
    img.fmt = AOM_IMG_FMT_I420;
    img.w = 640;
    img.h = 480;
    img.d_w = 640;
    img.d_h = 480;
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bps = 12;
    img.planes[0] = (uint8_t*)data;  // Use the input data as plane data
    img.planes[1] = (uint8_t*)data + size / 4;  // Offset for U plane
    img.planes[2] = (uint8_t*)data + size / 2;  // Offset for V plane
    img.stride[0] = 640;
    img.stride[1] = 320;
    img.stride[2] = 320;
    img.user_priv = NULL;
    img.img_data = (uint8_t*)data;
    img.img_data_owner = 1;
    img.self_allocd = 0;
    
    // Call the function-under-test
    aom_img_free(&img);
    
    return 0;
}