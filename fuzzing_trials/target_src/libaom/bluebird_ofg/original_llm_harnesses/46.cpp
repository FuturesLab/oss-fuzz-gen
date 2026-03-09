#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize an aom_image_t structure
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t));

    // Set some non-NULL values for the aom_image_t structure
    img.fmt = AOM_IMG_FMT_I420;
    img.w = 640;
    img.h = 480;
    img.d_w = 640;
    img.d_h = 480;
    img.stride[0] = 640;
    img.stride[1] = 320;
    img.stride[2] = 320;
    img.planes[0] = (uint8_t *)malloc(640 * 480);
    img.planes[1] = (uint8_t *)malloc(320 * 240);
    img.planes[2] = (uint8_t *)malloc(320 * 240);

    // Ensure the data is not NULL and size is valid for metadata retrieval
    if (data != nullptr && size > 0) {
        // Call the function-under-test
        const aom_metadata_t *metadata = aom_img_get_metadata(&img, size);

        // Process the metadata if needed (for fuzzing purposes, we just check if it's not NULL)
        if (metadata != nullptr) {
            // Example processing (not doing anything specific here)
        }
    }

    // Free allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}