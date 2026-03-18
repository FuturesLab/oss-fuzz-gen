// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_wrap at aom_image.c:216:14 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_set_rect at aom_image.c:234:5 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_flip at aom_image.c:285:6 in aom_image.h
// aom_img_free at aom_image.c:304:6 in aom_image.h
// aom_img_alloc at aom_image.c:200:14 in aom_image.h
// aom_img_remove_metadata at aom_image.c:412:6 in aom_image.h
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
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom.h"
#include "aomcx.h"

static void fuzz_aom_img_alloc_and_free(const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure we have enough data

    aom_image_t *img = nullptr;
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 7); // Limit to known formats
    unsigned int d_w = (Data[1] << 8) | Data[2];
    unsigned int d_h = (Data[3] << 8) | Data[4];
    unsigned int align = (Data[5] << 8) | Data[6];

    img = aom_img_alloc(nullptr, fmt, d_w, d_h, align);
    if (img) {
        aom_img_free(img);
    }
}

static void fuzz_aom_img_wrap(const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure we have enough data

    aom_image_t img;
    memset(&img, 0, sizeof(img));
    aom_img_fmt_t fmt = static_cast<aom_img_fmt_t>(Data[0] % 7); // Limit to known formats
    unsigned int d_w = (Data[1] << 8) | Data[2];
    unsigned int d_h = (Data[3] << 8) | Data[4];
    unsigned int stride_align = (Data[5] << 8) | Data[6];

    unsigned char dummy_data[1024]; // Example buffer
    aom_image_t *wrapped_img = aom_img_wrap(&img, fmt, d_w, d_h, stride_align, dummy_data);
    if (wrapped_img) {
        aom_img_free(wrapped_img);
    }
}

static void fuzz_aom_img_set_rect(const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure we have enough data

    aom_image_t img;
    memset(&img, 0, sizeof(img));

    unsigned int x = (Data[0] << 8) | Data[1];
    unsigned int y = (Data[2] << 8) | Data[3];
    unsigned int w = (Data[4] << 8) | Data[5];
    unsigned int h = (Data[6] << 8) | Data[7];
    unsigned int border = (Data[8] << 8) | Data[9];

    aom_img_alloc(&img, AOM_IMG_FMT_I420, w + x, h + y, 1); // Ensure valid allocation
    aom_img_set_rect(&img, x, y, w, h, border);
    aom_img_free(&img);
}

static void fuzz_aom_img_flip(const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure we have enough data

    aom_image_t img;
    memset(&img, 0, sizeof(img));
    unsigned int d_w = (Data[0] << 8) | Data[1];
    unsigned int d_h = (Data[2] << 8) | Data[3];

    aom_img_alloc(&img, AOM_IMG_FMT_I420, d_w, d_h, 1); // Ensure valid allocation
    aom_img_flip(&img);
    aom_img_free(&img);
}

static void fuzz_aom_img_remove_metadata(const uint8_t *Data, size_t Size) {
    if (Size < 16) return; // Ensure we have enough data

    aom_image_t img;
    memset(&img, 0, sizeof(img));
    unsigned int d_w = (Data[0] << 8) | Data[1];
    unsigned int d_h = (Data[2] << 8) | Data[3];

    aom_img_alloc(&img, AOM_IMG_FMT_I420, d_w, d_h, 1); // Ensure valid allocation
    aom_img_remove_metadata(&img);
    aom_img_free(&img);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    fuzz_aom_img_alloc_and_free(Data, Size);
    fuzz_aom_img_wrap(Data, Size);
    fuzz_aom_img_set_rect(Data, Size);
    fuzz_aom_img_flip(Data, Size);
    fuzz_aom_img_remove_metadata(Data, Size);
    return 0;
}