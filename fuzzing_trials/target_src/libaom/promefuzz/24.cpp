// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_set_option at aom_codec.c:119:17 in aom_codec.h
// aom_codec_error at aom_codec.c:56:13 in aom_codec.h
// aom_codec_error_detail at aom_codec.c:61:13 in aom_codec.h
// aom_codec_encode at aom_encoder.c:168:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

static void initialize_codec_context(aom_codec_ctx_t &ctx) {
    memset(&ctx, 0, sizeof(aom_codec_ctx_t));
    ctx.iface = aom_codec_av1_cx();
    ctx.err = AOM_CODEC_OK;
}

static int set_codec_option(aom_codec_ctx_t &ctx, const char *name, const char *value) {
    return aom_codec_set_option(&ctx, name, value);
}

static const char* get_codec_error(aom_codec_ctx_t &ctx) {
    return aom_codec_error(&ctx);
}

static const char* get_codec_error_detail(aom_codec_ctx_t &ctx) {
    return aom_codec_error_detail(&ctx);
}

static int encode_frame(aom_codec_ctx_t &ctx, aom_image_t *img, aom_codec_pts_t pts, unsigned long duration, aom_enc_frame_flags_t flags) {
    return aom_codec_encode(&ctx, img, pts, duration, flags);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    initialize_codec_context(codec_ctx);

    // Fuzz the CQ level setting
    int cq_level = Data[0] % 64; // CQ level is typically between 0-63
    aom_codec_control(&codec_ctx, AOME_SET_CQ_LEVEL, cq_level);

    // Fuzz setting codec options
    const char *option_name = "cpu-used";
    char option_value[10];
    snprintf(option_value, sizeof(option_value), "%d", Data[0] % 9);
    set_codec_option(codec_ctx, option_name, option_value);

    // Fuzz encoding a frame
    aom_image_t img;
    memset(&img, 0, sizeof(aom_image_t));
    img.fmt = AOM_IMG_FMT_I420;
    img.w = 640;
    img.h = 480;
    img.planes[0] = const_cast<uint8_t*>(Data);
    img.stride[0] = 640;
    encode_frame(codec_ctx, &img, 0, 1, 0);

    // Retrieve errors
    const char *error_msg = get_codec_error(codec_ctx);
    const char *error_detail = get_codec_error_detail(codec_ctx);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}