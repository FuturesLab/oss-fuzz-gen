#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" {
    // Include the necessary headers for the function-under-test
    #include <aom/aom.h>
    #include <aom/aomcx.h> // Include the header where AOM_METADATA_INSERT_FLAG_NONE is likely defined
    #include <aom/aom_encoder.h> // Additional header where AOM_METADATA_INSERT_FLAG_NONE might be defined
}

// Function signature to be fuzzed
extern "C" int aom_img_add_metadata(aom_image_t *img, uint32_t type, const uint8_t *metadata, size_t metadata_size, aom_metadata_insert_flags_t flags);

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize the aom_image_t structure
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Example format
    img.w = 640; // Example width
    img.h = 480; // Example height
    img.d_w = img.w;
    img.d_h = img.h;
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bps = 12;
    img.planes[0] = (uint8_t *)malloc(img.w * img.h); // Allocate memory for Y plane
    img.planes[1] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // Allocate memory for U plane
    img.planes[2] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // Allocate memory for V plane
    img.stride[0] = img.w;
    img.stride[1] = img.w >> img.x_chroma_shift;
    img.stride[2] = img.w >> img.x_chroma_shift;

    // Ensure the data size is sufficient for metadata
    if (size < 1) {
        free(img.planes[0]);
        free(img.planes[1]);
        free(img.planes[2]);
        return 0;
    }

    // Set up the metadata and flags
    uint32_t type = 0; // Example type
    const uint8_t *metadata = data;
    size_t metadata_size = size;
    aom_metadata_insert_flags_t flags = static_cast<aom_metadata_insert_flags_t>(0); // Example flag, assuming 0 is a valid default

    // Call the function-under-test
    int result = aom_img_add_metadata(&img, type, metadata, metadata_size, flags);

    // Clean up
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}