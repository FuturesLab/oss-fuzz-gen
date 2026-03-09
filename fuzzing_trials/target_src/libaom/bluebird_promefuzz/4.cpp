#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aomcx.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 5) return 0;

    // Extract some test parameters from the input data
    uint32_t fmt = *reinterpret_cast<const uint32_t*>(Data);
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    uint32_t width = *reinterpret_cast<const uint32_t*>(Data) % 0x08000000;
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    uint32_t height = *reinterpret_cast<const uint32_t*>(Data) % 0x08000000;
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    uint32_t align = *reinterpret_cast<const uint32_t*>(Data) % 65536;
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    uint32_t plane_index = *reinterpret_cast<const uint32_t*>(Data) % 3;
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    // Allocate an image
    aom_image_t *img = aom_img_alloc(nullptr, static_cast<aom_img_fmt_t>(fmt), width, height, align);
    if (!img) return 0;

    // Test aom_img_plane_height and aom_img_plane_width
    int plane_height = aom_img_plane_height(img, plane_index);
    int plane_width = aom_img_plane_width(img, plane_index);

    // Test aom_img_flip
    aom_img_flip(img);

    // Test aom_img_set_rect with arbitrary rectangle
    unsigned int rect_x = width / 4;
    unsigned int rect_y = height / 4;
    unsigned int rect_w = width / 2;
    unsigned int rect_h = height / 2;
    unsigned int border = 0;
    aom_img_set_rect(img, rect_x, rect_y, rect_w, rect_h, border);

    // If there's remaining data, test aom_img_add_metadata
    if (Size >= sizeof(uint32_t) + 1) {
        uint32_t metadata_type = *reinterpret_cast<const uint32_t*>(Data);
        Data += sizeof(uint32_t);
        Size -= sizeof(uint32_t);

        aom_metadata_insert_flags_t insert_flag = static_cast<aom_metadata_insert_flags_t>(Data[0]);
        Data += 1;
        Size -= 1;

        int metadata_result = aom_img_add_metadata(img, metadata_type, Data, Size, insert_flag);
    }

    // Free the image
    aom_img_free(img);

    return 0;
}