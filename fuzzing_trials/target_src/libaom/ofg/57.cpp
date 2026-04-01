#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

// Ensure the function-under-test is called within the fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    aom_image_t img;

    // Initialize the aom_image_t structure with non-null values
    img.fmt = AOM_IMG_FMT_I420;  // Use a valid image format
    img.w = 640;                 // Set a default width
    img.h = 480;                 // Set a default height
    img.d_w = 640;               // Set a display width
    img.d_h = 480;               // Set a display height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.planes[0] = (uint8_t *)data;  // Assign data to the first plane
    img.stride[0] = (int)size;        // Set stride to the size of the data

    // Call the function-under-test
    size_t num_metadata = aom_img_num_metadata(&img);

    // Use the result to prevent compiler optimizations
    if (num_metadata == 0) {
        return 0;
    }

    return 0;
}