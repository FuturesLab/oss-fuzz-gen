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
#include <cstring>
#include <cstdlib>
#include "aom/aomdx.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aomcx.h"
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom.h"
#include "aom/aom_decoder.h"

static aom_image_t* create_dummy_image() {
    aom_image_t* img = (aom_image_t*)malloc(sizeof(aom_image_t));
    if (!img) return nullptr;
    img->fmt = AOM_IMG_FMT_I420;
    img->w = 640;
    img->h = 480;
    img->stride[0] = img->w;
    img->stride[1] = img->stride[2] = img->w / 2;
    img->planes[0] = (unsigned char*)malloc(img->h * img->stride[0]);
    img->planes[1] = (unsigned char*)malloc(img->h / 2 * img->stride[1]);
    img->planes[2] = (unsigned char*)malloc(img->h / 2 * img->stride[2]);
    return img;
}

static void destroy_dummy_image(aom_image_t* img) {
    if (img) {
        free(img->planes[0]);
        free(img->planes[1]);
        free(img->planes[2]);
        free(img);
    }
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(aom_image_t)) return 0;

    aom_codec_ctx_t ctx;
    aom_image_t* img = create_dummy_image();
    if (!img) return 0;

    aom_codec_err_t res;
    aom_codec_pts_t pts = 0;
    unsigned long duration = 1;
    aom_enc_frame_flags_t flags = 0;

    // Fuzzing aom_codec_encode
    res = aom_codec_encode(&ctx, img, pts, duration, flags);
    if (res != AOM_CODEC_OK) {
        const char* err_msg = aom_codec_error(&ctx);
        fprintf(stderr, "Error: %s\n", err_msg);
    }

    // Fuzzing aom_codec_destroy
    res = aom_codec_destroy(&ctx);
    if (res != AOM_CODEC_OK) {
        const char* err_msg = aom_codec_error(&ctx);
        fprintf(stderr, "Destroy Error: %s\n", err_msg);
    }

    // Fuzzing aom_codec_set_option
    res = aom_codec_set_option(&ctx, "dummy_option", "dummy_value");
    if (res != AOM_CODEC_OK) {
        const char* err_msg = aom_codec_error(&ctx);
        fprintf(stderr, "Set Option Error: %s\n", err_msg);
    }

    destroy_dummy_image(img);
    return 0;
}