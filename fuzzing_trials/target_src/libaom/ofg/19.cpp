#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>

extern "C" {
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to initialize the parameters
    if (size < sizeof(aom_image_t) + sizeof(int)) {
        return 0;
    }

    // Initialize aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = 640; // Display width
    img.d_h = 480; // Display height
    img.x_chroma_shift = 1; // Example chroma shift
    img.y_chroma_shift = 1; // Example chroma shift

    // Use part of the data to initialize 'plane'
    int plane = static_cast<int>(data[0] % 3); // Assuming 3 planes (Y, U, V)

    // Call the function-under-test
    int height = aom_img_plane_height(&img, plane);

    // Use the result in some way to avoid compiler optimizations
    volatile int result = height;
    (void)result;

    return 0;
}