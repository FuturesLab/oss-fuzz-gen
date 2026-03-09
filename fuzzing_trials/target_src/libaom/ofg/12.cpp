#include <cstdint>
#include <cstdlib>
#include <aom/aom_image.h> // Include the necessary header for aom_image_t

extern "C" int aom_img_plane_width(const aom_image_t *, int);

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Declare and initialize the variables
    aom_image_t img;
    int plane = 0;

    // Initialize the aom_image_t structure with some non-NULL values
    img.fmt = AOM_IMG_FMT_I420; // Use a valid image format
    img.w = 640; // Width of the image
    img.h = 480; // Height of the image
    img.d_w = 640; // Displayed width
    img.d_h = 480; // Displayed height
    img.x_chroma_shift = 1;
    img.y_chroma_shift = 1;
    img.planes[0] = const_cast<uint8_t*>(data); // Assign data to the first plane
    img.planes[1] = const_cast<uint8_t*>(data); // Assign data to the second plane
    img.planes[2] = const_cast<uint8_t*>(data); // Assign data to the third plane
    img.stride[0] = 640;
    img.stride[1] = 320;
    img.stride[2] = 320;

    // Call the function-under-test
    int width = aom_img_plane_width(&img, plane);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}