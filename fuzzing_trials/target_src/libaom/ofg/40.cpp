#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    aom_image_t img;
    aom_img_fmt_t format = AOM_IMG_FMT_I420;  // Example format
    unsigned int width = 640;                 // Example width
    unsigned int height = 480;                // Example height
    unsigned int stride = 640;                // Example stride

    // Ensure the data size is sufficient for the image buffer
    if (size < width * height * 3 / 2) {
        return 0;  // Not enough data for a YUV 4:2:0 image
    }

    unsigned char *img_data = const_cast<unsigned char *>(data);

    // Call the function-under-test
    aom_image_t *wrapped_img = aom_img_wrap(&img, format, width, height, stride, img_data);

    // Use the wrapped image (wrapped_img) here if needed for further testing

    return 0;
}