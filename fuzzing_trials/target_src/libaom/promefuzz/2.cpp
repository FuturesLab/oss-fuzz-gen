// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_flip at aom_image.c:285:6 in aom_image.h
// aom_img_set_rect at aom_image.c:234:5 in aom_image.h
// aom_img_wrap at aom_image.c:216:14 in aom_image.h
// aom_img_flip at aom_image.c:285:6 in aom_image.h
// aom_img_alloc_with_border at aom_image.c:225:14 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
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
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
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