#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure that the input data size is sufficient for our needs
    if (size < 20) {
        return 0;
    }

    // Initialize the variables required for the function call
    aom_image_t img;
    unsigned int x = static_cast<unsigned int>(data[0]);
    unsigned int y = static_cast<unsigned int>(data[1]);
    unsigned int w = static_cast<unsigned int>(data[2]);
    unsigned int h = static_cast<unsigned int>(data[3]);
    unsigned int border = static_cast<unsigned int>(data[4]);

    // Initialize the image structure with some non-null values
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.d_w = 640; // Example width
    img.d_h = 480; // Example height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bps = 12;
    img.bit_depth = 8;
    img.planes[0] = const_cast<uint8_t *>(data + 5); // Example plane data
    img.stride[0] = 640; // Example stride

    // Call the function under test
    int result = aom_img_set_rect(&img, x, y, w, h, border);

    // Return 0 to indicate successful execution of the fuzzer
    return 0;
}