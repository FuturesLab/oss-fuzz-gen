// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_img_set_rect at vpx_image.c:176:5 in vpx_image.h
// vpx_img_wrap at vpx_image.c:168:14 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_codec_get_frame at vpx_decoder.c:122:14 in vpx_decoder.h
// vpx_img_flip at vpx_image.c:229:6 in vpx_image.h
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include "vpx/vpx_decoder.h"
#include "vpx/vp8cx.h"
#include "vpx/vp8dx.h"
#include "vpx/vpx_image.h"

static void fuzz_vpx_img_set_rect(vpx_image_t *img, const uint8_t *Data, size_t Size) {
    if (Size < 4 * sizeof(unsigned int)) return;

    unsigned int x = *(reinterpret_cast<const unsigned int *>(Data));
    unsigned int y = *(reinterpret_cast<const unsigned int *>(Data + sizeof(unsigned int)));
    unsigned int w = *(reinterpret_cast<const unsigned int *>(Data + 2 * sizeof(unsigned int)));
    unsigned int h = *(reinterpret_cast<const unsigned int *>(Data + 3 * sizeof(unsigned int)));

    vpx_img_set_rect(img, x, y, w, h);
}

static void fuzz_vpx_img_wrap(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_img_fmt_t) + 3 * sizeof(unsigned int) + sizeof(unsigned char *)) return;

    vpx_img_fmt_t fmt = static_cast<vpx_img_fmt_t>(*(reinterpret_cast<const int *>(Data)));
    unsigned int d_w = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t)));
    unsigned int d_h = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t) + sizeof(unsigned int)));
    unsigned int stride_align = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t) + 2 * sizeof(unsigned int)));
    unsigned char *img_data = const_cast<unsigned char *>(Data + sizeof(vpx_img_fmt_t) + 3 * sizeof(unsigned int));

    vpx_image_t *img = vpx_img_wrap(nullptr, fmt, d_w, d_h, stride_align, img_data);
    if (img) {
        vpx_img_free(img);
    }
}

static void fuzz_vpx_img_alloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_img_fmt_t) + 3 * sizeof(unsigned int)) return;

    vpx_img_fmt_t fmt = static_cast<vpx_img_fmt_t>(*(reinterpret_cast<const int *>(Data)));
    unsigned int d_w = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t)));
    unsigned int d_h = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t) + sizeof(unsigned int)));
    unsigned int align = *(reinterpret_cast<const unsigned int *>(Data + sizeof(vpx_img_fmt_t) + 2 * sizeof(unsigned int)));

    vpx_image_t *img = vpx_img_alloc(nullptr, fmt, d_w, d_h, align);
    if (img) {
        vpx_img_free(img);
    }
}

static void fuzz_vpx_codec_get_frame(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_codec_ctx_t)) return;

    vpx_codec_ctx_t ctx;
    memset(&ctx, 0, sizeof(vpx_codec_ctx_t)); // Initialize the context to avoid undefined behavior

    vpx_codec_iter_t iter = nullptr;

    vpx_image_t *img = vpx_codec_get_frame(&ctx, &iter);
    (void)img; // Avoid unused variable warning
}

static void fuzz_vpx_img_flip(vpx_image_t *img) {
    vpx_img_flip(img);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_image_t)) return 0;

    vpx_image_t img;
    memcpy(&img, Data, sizeof(vpx_image_t));

    fuzz_vpx_img_set_rect(&img, Data, Size);
    fuzz_vpx_img_wrap(Data, Size);
    fuzz_vpx_img_alloc(Data, Size);
    fuzz_vpx_codec_get_frame(Data, Size);
    fuzz_vpx_img_flip(&img);

    return 0;
}