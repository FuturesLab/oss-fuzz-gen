// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_img_alloc at vpx_image.c:162:14 in vpx_image.h
// vpx_img_set_rect at vpx_image.c:176:5 in vpx_image.h
// vpx_img_flip at vpx_image.c:229:6 in vpx_image.h
// vpx_img_wrap at vpx_image.c:168:14 in vpx_image.h
// vpx_codec_get_frame at vpx_decoder.c:122:14 in vpx_decoder.h
// vpx_codec_get_preview_frame at vpx_encoder.c:314:20 in vpx_encoder.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
// vpx_img_free at vpx_image.c:252:6 in vpx_image.h
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
#include "vpx_image.h"
#include "vpx/vp8cx.h"
#include "vpx/vpx_decoder.h"
#include "vpx/vpx_encoder.h"
#include "vpx/vp8dx.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_img_fmt_t) + 4 * sizeof(unsigned int) + sizeof(int)) {
        return 0;
    }

    const vpx_img_fmt_t fmt = static_cast<vpx_img_fmt_t>(Data[0] % 10);
    unsigned int d_w = (Data[1] << 8) | Data[2];
    unsigned int d_h = (Data[3] << 8) | Data[4];
    unsigned int align = Data[5] % 65536;
    unsigned int stride_align = Data[6] % 65536;

    // Allocate or wrap an image
    vpx_image_t *img = vpx_img_alloc(NULL, fmt, d_w, d_h, align);
    if (!img) {
        return 0;
    }

    // Set a rectangle
    unsigned int x = Data[7] % (img->w ? img->w : 1);
    unsigned int y = Data[8] % (img->h ? img->h : 1);
    unsigned int w = Data[9] % (img->w - x + 1);
    unsigned int h = Data[10] % (img->h - y + 1);
    vpx_img_set_rect(img, x, y, w, h);

    // Flip the image
    vpx_img_flip(img);

    // Wrap an image
    unsigned char *img_data = new unsigned char[d_w * d_h * 4];
    vpx_image_t *wrapped_img = vpx_img_wrap(NULL, fmt, d_w, d_h, stride_align, img_data);

    // Codec context setup
    vpx_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    vpx_codec_iter_t iter = NULL;
    vpx_codec_get_frame(&codec_ctx, &iter);
    vpx_codec_get_preview_frame(&codec_ctx);

    // Clean up
    vpx_img_free(img);
    if (wrapped_img) {
        vpx_img_free(wrapped_img);
    }
    delete[] img_data;

    return 0;
}