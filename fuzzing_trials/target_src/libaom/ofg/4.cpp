#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>

extern "C" int aom_img_add_metadata(aom_image_t *img, uint32_t type, const uint8_t *metadata, size_t metadata_size, aom_metadata_insert_flags_t flags);

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure size is large enough to extract necessary parameters
    if (size < sizeof(uint32_t) + sizeof(aom_metadata_insert_flags_t)) {
        return 0;
    }

    // Initialize aom_image_t
    aom_image_t img;
    img.fmt = AOM_IMG_FMT_I420; // Use a valid format
    img.w = 640; // Set a reasonable width
    img.h = 480; // Set a reasonable height
    img.d_w = img.w; // Display width
    img.d_h = img.h; // Display height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.bps = 12;
    img.planes[0] = (uint8_t *)malloc(img.w * img.h); // Allocate memory for Y plane
    img.planes[1] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // Allocate memory for U plane
    img.planes[2] = (uint8_t *)malloc((img.w >> img.x_chroma_shift) * (img.h >> img.y_chroma_shift)); // Allocate memory for V plane
    img.stride[0] = img.w;
    img.stride[1] = img.w >> img.x_chroma_shift;
    img.stride[2] = img.w >> img.x_chroma_shift;

    // Extract parameters from data
    uint32_t type = *(reinterpret_cast<const uint32_t *>(data));
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    aom_metadata_insert_flags_t flags = *(reinterpret_cast<const aom_metadata_insert_flags_t *>(data));
    data += sizeof(aom_metadata_insert_flags_t);
    size -= sizeof(aom_metadata_insert_flags_t);

    // Call the function-under-test
    aom_img_add_metadata(&img, type, data, size, flags);

    // Free allocated memory
    free(img.planes[0]);
    free(img.planes[1]);
    free(img.planes[2]);

    return 0;
}