// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc_with_border at aom_image.c:225:14 in aom_image.h
// aom_img_set_rect at aom_image.c:234:5 in aom_image.h
// aom_img_plane_width at aom_image.c:313:5 in aom_image.h
// aom_img_plane_height at aom_image.c:320:5 in aom_image.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 41) return 0; // Ensure we have enough data

    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 8); // Randomly select format
    unsigned int d_w = *(reinterpret_cast<const unsigned int*>(Data + 1)) % 0x08000000; // Width
    unsigned int d_h = *(reinterpret_cast<const unsigned int*>(Data + 5)) % 0x08000000; // Height
    unsigned int align = *(reinterpret_cast<const unsigned int*>(Data + 9)) % 65536; // Alignment
    unsigned int size_align = *(reinterpret_cast<const unsigned int*>(Data + 13)) % 65536; // Size alignment
    unsigned int border = *(reinterpret_cast<const unsigned int*>(Data + 17)) % 65536; // Border

    // Test aom_img_alloc_with_border
    img = aom_img_alloc_with_border(img, fmt, d_w, d_h, align, size_align, border);
    if (img) {
        // Test aom_img_set_rect with random values
        unsigned int x = *(reinterpret_cast<const unsigned int*>(Data + 21)) % (d_w + 1); // Ensure x <= d_w
        unsigned int y = *(reinterpret_cast<const unsigned int*>(Data + 25)) % (d_h + 1); // Ensure y <= d_h
        unsigned int w = (d_w - x) ? *(reinterpret_cast<const unsigned int*>(Data + 29)) % (d_w - x) : 0;
        unsigned int h = (d_h - y) ? *(reinterpret_cast<const unsigned int*>(Data + 33)) % (d_h - y) : 0;

        // Ensure w and h are valid
        if (w + x > d_w) w = d_w - x;
        if (h + y > d_h) h = d_h - y;

        aom_img_set_rect(img, x, y, w, h, border);

        // Test aom_img_plane_width and aom_img_plane_height
        for (int plane = 0; plane < 3; ++plane) {
            aom_img_plane_width(img, plane);
            aom_img_plane_height(img, plane);
        }

        // Free the image
        aom_img_free(img);
    }

    return 0;
}