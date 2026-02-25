#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Include the necessary headers for the aom_image_t type
extern "C" {
#include <aom/aom_image.h>
#include <aom/aom_decoder.h> // Include for AOM_METADATA_INSERT_FLAG_NONE
}

// Define the metadata insert flags if not defined
#ifndef AOM_METADATA_INSERT_FLAG_NONE
#define AOM_METADATA_INSERT_FLAG_NONE 0
#endif

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    aom_image_t img;
    uint32_t metadata_id = 1; // Example metadata ID
    const uint8_t *metadata_data = data; // Use the input data as metadata
    size_t metadata_size = size; // Size of the metadata
    aom_metadata_insert_flags_t flags = static_cast<aom_metadata_insert_flags_t>(AOM_METADATA_INSERT_FLAG_NONE); // Correctly cast to enum type

    // Initialize the aom_image_t structure
    img.fmt = AOM_IMG_FMT_I420; // Set image format
    img.w = 640; // Set image width
    img.h = 480; // Set image height
    img.d_w = img.w; // Set display width
    img.d_h = img.h; // Set display height
    img.planes[0] = (uint8_t *)malloc(img.w * img.h); // Allocate memory for Y plane
    img.planes[1] = (uint8_t *)malloc(img.w * img.h / 4); // Allocate memory for U plane
    img.planes[2] = (uint8_t *)malloc(img.w * img.h / 4); // Allocate memory for V plane

    // Call the function to fuzz
    int result = aom_img_add_metadata(&img, metadata_id, metadata_data, metadata_size, flags);

    // Free allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return result;
}