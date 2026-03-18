extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t img;
    int plane = 0; // Assuming plane 0 for testing

    // Initialize the image structure with some non-NULL values
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = 640; // Display width
    img.d_h = 480; // Display height
    img.x_chroma_shift = 1; // Example chroma shift
    img.y_chroma_shift = 1; // Example chroma shift
    img.bps = 12; // Example bits per sample

    // Call the function-under-test
    int height = aom_img_plane_height(&img, plane);

    // Return 0 as required by the fuzzer
    return 0;
}