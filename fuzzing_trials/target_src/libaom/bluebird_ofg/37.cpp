#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "/src/aom/aom/aom_image.h"

extern "C" {
    int aom_img_plane_height(const aom_image_t *img, int plane);
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Initialize aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Set a valid format
    img.w = 640; // Set a valid width
    img.h = 480; // Set a valid height
    img.d_w = 640; // Displayed width
    img.d_h = 480; // Displayed height
    img.x_chroma_shift = 1; // Chroma shift
    img.y_chroma_shift = 1; // Chroma shift
    img.bps = 12; // Bits per sample

    // Use the data to set the plane index
    int plane = data[0] % 3; // Assuming 3 planes (Y, U, V)

    // Call the function-under-test
    int height = aom_img_plane_height(&img, plane);

    // Output the result (for debugging purposes)
    std::cout << "Plane: " << plane << ", Height: " << height << std::endl;

    return 0;
}