#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>

extern "C" {

size_t aom_img_num_metadata(const aom_image_t *img);

}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure size is within a reasonable limit for aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create and initialize an aom_image_t structure
    aom_image_t *img = (aom_image_t *)malloc(sizeof(aom_image_t));
    if (img == nullptr) {
        return 0; // Ensure img is not NULL
    }

    // Initialize the aom_image_t structure with data from the input
    // Here we assume the input data can be used to fill the structure
    // This is a simplified initialization for demonstration purposes.
    std::memset(img, 0, sizeof(aom_image_t)); // Clear the structure
    img->fmt = AOM_IMG_FMT_I420; // Set a valid format
    img->d_w = 1280; // Set width
    img->d_h = 720; // Set height
    img->planes[0] = (uint8_t *)data; // Set the first plane to point to input data
    img->planes[1] = img->planes[0] + (1280 * 720); // Set second plane
    img->planes[2] = img->planes[1] + (640 * 360); // Set third plane

    // Call the function under test
    size_t metadata_count = aom_img_num_metadata(img);

    // Cleanup
    free(img);

    return 0;
}