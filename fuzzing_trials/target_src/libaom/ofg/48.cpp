#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_image.h>

extern "C" {
    // Include necessary AOM headers
    #include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Declare and initialize an aom_image_t object
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t)); // Initialize the structure to zero

    // Populate the aom_image_t structure with valid data
    img.fmt = AOM_IMG_FMT_I420; // Set a valid image format
    img.w = 640; // Set a valid width
    img.h = 480; // Set a valid height
    img.stride[0] = 640; // Set the stride for the Y plane
    img.stride[1] = 320; // Set the stride for the U plane
    img.stride[2] = 320; // Set the stride for the V plane
    img.planes[0] = (uint8_t *)data; // Assign the input data to the Y plane
    img.planes[1] = img.planes[0] + (640 * 480); // Assign U plane
    img.planes[2] = img.planes[1] + (320 * 240); // Assign V plane

    // Call the function under test with the aom_image_t and a valid plane index
    int plane_index = 0; // Testing for the Y plane
    int height = aom_img_plane_height(&img, plane_index);

    // Optionally, you can check the height value or perform additional processing
    // For this fuzzing harness, we just return
    return 0;
}