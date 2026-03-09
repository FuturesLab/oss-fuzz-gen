#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
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
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_img_fmt_t) + 3 * sizeof(unsigned int)) {
        return 0; // Not enough data
    }

    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0]);
    unsigned int d_w = static_cast<unsigned int>(Data[1]) % 0x08000000;
    unsigned int d_h = static_cast<unsigned int>(Data[2]) % 0x08000000;
    unsigned int align = static_cast<unsigned int>(Data[3]) % 65536;

    aom_image_t *img = nullptr;
    aom_image_t *wrapped_img = nullptr;

    // Test aom_img_alloc
    img = aom_img_alloc(nullptr, fmt, d_w, d_h, align);
    if (img) {
        // Test aom_img_flip
        aom_img_flip(img);

        // Test aom_img_set_rect
        unsigned int border = 0;
        aom_img_set_rect(img, 0, 0, d_w, d_h, border);

        // Test aom_img_wrap
        wrapped_img = aom_img_wrap(img, fmt, d_w, d_h, align, img->img_data);
        if (wrapped_img) {
            aom_img_flip(wrapped_img);
        }

        // Test aom_img_alloc_with_border
        aom_image_t *border_img = aom_img_alloc_with_border(nullptr, fmt, d_w, d_h, align, align, border);
        if (border_img) {
            aom_img_free(border_img);
        }

        aom_img_free(img);
    }

    if (wrapped_img && wrapped_img != img) {
        aom_img_free(wrapped_img);
    }

    return 0;
}