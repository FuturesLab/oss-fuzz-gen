#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" {
    aom_image_t * aom_img_alloc(aom_image_t *img, aom_img_fmt_t fmt, unsigned int width, unsigned int height, unsigned int align);
    
    // Define AOM_IMG_FMT_COUNT if it's not defined in the included headers
    #ifndef AOM_IMG_FMT_COUNT
    #define AOM_IMG_FMT_COUNT 5 // Adjust this value based on the actual number of formats defined in aom_img_fmt_t
    #endif
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure that size is within reasonable bounds for width and height
    if (size < 8) {
        return 0; // Not enough data to proceed
    }

    // Initialize parameters for aom_img_alloc
    aom_image_t *img = nullptr; // img parameter, can be NULL
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(data[0] % AOM_IMG_FMT_COUNT); // Use first byte for format
    unsigned int width = static_cast<unsigned int>(data[1] % 1920); // Width, limit to 1920
    unsigned int height = static_cast<unsigned int>(data[2] % 1080); // Height, limit to 1080
    unsigned int align = static_cast<unsigned int>(data[3] % 16); // Alignment, limit to 16

    // Call the function under test
    aom_image_t *result = aom_img_alloc(img, fmt, width, height, align);

    // Clean up if necessary (the function may return NULL)
    if (result != nullptr) {
        // Normally you would free the image here, but for fuzzing we just let it be
        // aom_img_free(result); // Uncomment if you need to free the image
    }

    return 0;
}