#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Assuming the definition of aom_image_t is provided in the relevant AOM header file
extern "C" {
#include <aom/aom_image.h>
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid aom_image_t
    if (size < sizeof(aom_image_t)) {
        return 0;
    }

    // Create and initialize an aom_image_t structure
    aom_image_t img;
    std::memset(&img, 0, sizeof(aom_image_t)); // Zero-initialize the structure

    // Fill the aom_image_t structure with data from the input
    // Here, we will assume the input data can be used to fill the fields of aom_image_t
    // Adjust the following fields based on the actual structure definition of aom_image_t
    img.fmt = AOM_IMG_FMT_I420; // Example format, replace with valid one as needed
    img.w = static_cast<int>(data[0]) % 1920; // Width, limited to a reasonable range
    img.h = static_cast<int>(data[1]) % 1080; // Height, limited to a reasonable range
    img.stride[0] = img.w; // Assuming stride is equal to width for the first plane
    img.stride[1] = img.w / 2; // Assuming YUV format, adjust as necessary
    img.stride[2] = img.w / 2; // Assuming YUV format, adjust as necessary
    img.planes[0] = const_cast<uint8_t*>(data + 2); // Point to the input data
    img.planes[1] = img.planes[0] + img.w * img.h; // Y plane
    img.planes[2] = img.planes[1] + (img.w / 2) * (img.h / 2); // U plane

    // Call the function under test
    size_t metadata_count = aom_img_num_metadata(&img);

    // Optionally, you can process or log metadata_count if needed

    return 0;
}