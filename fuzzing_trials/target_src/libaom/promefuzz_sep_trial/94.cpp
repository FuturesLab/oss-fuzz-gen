// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1796:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_set_frame_buffer_functions at aom_decoder.c:120:17 in aom_decoder.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize decoder context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg;
    cfg.threads = 1;  // Default thread count

    // Initialize the decoder
    aom_codec_err_t res = aom_codec_dec_init_ver(&codec_ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Set up a dummy stream info structure
    aom_codec_stream_info_t stream_info;
    stream_info.w = 0;

    // Get stream info
    res = aom_codec_get_stream_info(&codec_ctx, &stream_info);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Decode data
    res = aom_codec_decode(&codec_ctx, Data, Size, nullptr);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Set frame buffer functions: Dummy callbacks
    auto cb_get = [](void *priv, size_t min_size, aom_codec_frame_buffer_t *fb) -> int {
        return 0;
    };
    auto cb_release = [](void *priv, aom_codec_frame_buffer_t *fb) -> int {
        return 0;
    };

    res = aom_codec_set_frame_buffer_functions(&codec_ctx, cb_get, cb_release, nullptr);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Retrieve codec capabilities
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}