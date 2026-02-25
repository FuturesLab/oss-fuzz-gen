#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include the necessary headers for aom_image_t and aom_img_flip
    #include "aom/aom_image.h"
}

// Define the fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Allocate and initialize an aom_image_t structure
    aom_image_t *img = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (img == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the aom_image_t structure with data from the input
    memcpy(img, data, sizeof(aom_image_t));

    // Call the function under test
    aom_img_flip(img);

    // Free the allocated memory
    free(img);

    return 0;
}