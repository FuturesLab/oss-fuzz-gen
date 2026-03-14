extern "C" {
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_image_t img;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int w = 1;
    unsigned int h = 1;
    unsigned int border = 0;

    // Ensure the image is initialized with non-NULL values
    aom_img_alloc(&img, AOM_IMG_FMT_I420, 16, 16, 1);

    // Call the function-under-test
    int result = aom_img_set_rect(&img, x, y, w, h, border);

    // Clean up
    aom_img_free(&img);

    return 0;
}