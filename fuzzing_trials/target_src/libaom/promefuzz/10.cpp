// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_flip at aom_image.c:285:6 in aom_image.h
// aom_img_set_rect at aom_image.c:234:5 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_alloc_with_border at aom_image.c:225:14 in aom_image.h
// aom_img_wrap at aom_image.c:216:14 in aom_image.h
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
#include <iostream>
#include <aom/aom_image.h>
#include <aom/aom_codec.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_encoder.h>
#include <aom/aom_external_partition.h>
#include <aom/aom.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_image_t *img = nullptr;
    unsigned int width = 640;
    unsigned int height = 480;
    unsigned int align = 32;
    unsigned int size_align = 32;
    unsigned int border = 32;

    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 8);

    // Allocate an image
    img = aom_img_alloc(nullptr, fmt, width, height, align);
    if (!img) return 0;

    // Flip the image
    aom_img_flip(img);

    // Set a rectangle
    unsigned int x = 0, y = 0, w = width / 2, h = height / 2;
    aom_img_set_rect(img, x, y, w, h, border);

    // Free the image
    aom_img_free(img);

    // Allocate with border
    img = aom_img_alloc_with_border(nullptr, fmt, width, height, align, size_align, border);
    if (!img) return 0;

    // Wrap an image
    unsigned char *img_data = new unsigned char[width * height * 3 / 2];
    aom_img_wrap(img, fmt, width, height, align, img_data);

    // Free the image
    aom_img_free(img);
    delete[] img_data;

    return 0;
}