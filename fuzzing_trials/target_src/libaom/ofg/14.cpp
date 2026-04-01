#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    // Function signature from the project under test
    int aom_img_plane_width(const aom_image_t *img, int plane);
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Initialize aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Use a valid image format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = 640; // Display width
    img.d_h = 480; // Display height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bit_depth = 8;
    img.planes[0] = const_cast<uint8_t*>(data); // Use input data as plane data

    // Use a valid plane index, typically 0 (Y), 1 (U), or 2 (V) for I420 format
    int plane = 0;

    // Call the function under test
    int width = aom_img_plane_width(&img, plane);

    // Optionally, use the result to prevent optimization out
    (void)width;

    return 0;
}