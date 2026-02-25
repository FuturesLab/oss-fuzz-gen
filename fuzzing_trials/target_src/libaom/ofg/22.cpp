#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>
#include <aom/aom_decoder.h>

extern "C" {

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize parameters for aom_img_alloc
    aom_image_t *img = nullptr; // aom_image_t pointer, initialized to NULL
    aom_img_fmt_t fmt = AOM_IMG_FMT_I420; // Use a common image format
    unsigned int width = 640; // Set a reasonable width
    unsigned int height = 480; // Set a reasonable height
    unsigned int align = 1; // Alignment, typically 1

    // Call the function under test
    img = aom_img_alloc(img, fmt, width, height, align);

    // Check if the image allocation was successful
    if (img != nullptr) {
        // Optionally, you could manipulate the image data here
        // For fuzzing purposes, we can just free the image
        aom_img_free(img);
    }

    return 0; // Return success
}

}