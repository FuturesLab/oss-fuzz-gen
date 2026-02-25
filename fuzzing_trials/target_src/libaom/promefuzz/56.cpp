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

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < 20) return 0;  // Ensure enough data for parameters

    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 8); // Random format
    unsigned int d_w = static_cast<unsigned int>(Data[1] % 1000); // Width
    unsigned int d_h = static_cast<unsigned int>(Data[2] % 1000); // Height
    unsigned int align = static_cast<unsigned int>(Data[3] % 65536); // Alignment
    unsigned int size_align = static_cast<unsigned int>(Data[4] % 65536); // Size alignment
    unsigned int border = static_cast<unsigned int>(Data[5] % 65536); // Border

    // Step 1: Allocate image with border
    img = aom_img_alloc_with_border(img, fmt, d_w, d_h, align, size_align, border);
    if (img) {
        // Step 2: Set rectangle with random values
        unsigned int x = static_cast<unsigned int>(Data[6] % (d_w + 1)); // Ensure x is within bounds
        unsigned int y = static_cast<unsigned int>(Data[7] % (d_h + 1)); // Ensure y is within bounds
        unsigned int w = static_cast<unsigned int>(Data[8] % (d_w - x + 1)); // Ensure width is valid
        unsigned int h = static_cast<unsigned int>(Data[9] % (d_h - y + 1)); // Ensure height is valid

        // Ensure the rectangle is valid before setting it
        if (x + w <= d_w && y + h <= d_h) {
            aom_img_set_rect(img, x, y, w, h, border);
        }

        // Step 3: Access plane dimensions
        for (int plane = 0; plane < 3; ++plane) {
            int width = aom_img_plane_width(img, plane);
            int height = aom_img_plane_height(img, plane);
        }

        // Step 4: Free the image
        aom_img_free(img);
    }

    return 0;
}