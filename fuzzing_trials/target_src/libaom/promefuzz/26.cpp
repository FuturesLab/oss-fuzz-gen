// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1796:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_set_frame_buffer_functions at aom_decoder.c:120:17 in aom_decoder.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_get_frame at aom_decoder.c:109:14 in aom_decoder.h
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
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aomcx.h"
#include "aomdx.h"

static int get_frame_buffer(void *priv, size_t min_size, aom_codec_frame_buffer_t *fb) {
    if (!priv || !fb) return -1;
    if (fb->data == NULL || fb->size < min_size) {
        fb->data = static_cast<uint8_t*>(realloc(fb->data, min_size));
        if (!fb->data) return -1;
        fb->size = min_size;
    }
    return 0;
}

static int release_frame_buffer(void *priv, aom_codec_frame_buffer_t *fb) {
    if (!priv || !fb) return -1;
    free(fb->data);
    fb->data = NULL;
    fb->size = 0;
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.threads = 1;

    if (aom_codec_dec_init_ver(&codec_ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION) != AOM_CODEC_OK) {
        return 0;
    }

    aom_codec_set_frame_buffer_functions(&codec_ctx, get_frame_buffer, release_frame_buffer, NULL);

    aom_codec_stream_info_t stream_info;
    memset(&stream_info, 0, sizeof(stream_info));

    aom_codec_get_stream_info(&codec_ctx, &stream_info);

    void *user_priv = NULL;
    aom_codec_decode(&codec_ctx, Data, Size, user_priv);

    aom_codec_iter_t iter = NULL;
    while (aom_codec_get_frame(&codec_ctx, &iter)) {
        // Process the frame
    }

    aom_codec_destroy(&codec_ctx);

    return 0;
}