#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" int aom_img_plane_width(const aom_image_t *img, int plane);

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t img;
    int plane;

    // Ensure the size is large enough to extract necessary information
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the image structure with non-null values
    img.fmt = AOM_IMG_FMT_I420;  // Example format
    img.w = 640;                 // Example width
    img.h = 480;                 // Example height
    img.d_w = 640;               // Example display width
    img.d_h = 480;               // Example display height
    img.x_chroma_shift = 1;      // Example chroma shift
    img.y_chroma_shift = 1;      // Example chroma shift
    img.bps = 12;                // Example bits per sample

    // Extract the plane value from the input data
    plane = static_cast<int>(data[0] % 3); // Assuming 3 planes for I420 format

    // Call the function under test
    int width = aom_img_plane_width(&img, plane);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}