#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Set a valid format
    img.w = 640; // Set a valid width
    img.h = 480; // Set a valid height
    img.d_w = 640; // Display width
    img.d_h = 480; // Display height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bit_depth = 8;
    img.img_data = const_cast<uint8_t*>(data); // Use input data as image data
    img.img_data_owner = 0;
    img.self_allocd = 0;
    img.bps = 12; // Bits per sample
    img.planes[0] = const_cast<uint8_t*>(data); // Use input data for plane
    img.stride[0] = 640; // Set stride for plane

    // Call the function-under-test
    size_t metadata_count = aom_img_num_metadata(&img);

    // Return 0 as required by LLVMFuzzerTestOneInput
    return 0;
}