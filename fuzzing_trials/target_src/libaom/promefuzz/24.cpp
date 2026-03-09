// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1796:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_peek_stream_info at aom_decoder.c:57:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_get_preview_frame at aom_encoder.c:264:20 in aom_encoder.h
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
#include <cstdlib>
#include <cstring>
#include <iostream>
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

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0};
    aom_codec_flags_t flags = 0;
    int ver = AOM_DECODER_ABI_VERSION;

    // Initialize the decoder
    aom_codec_err_t res = aom_codec_dec_init_ver(&codec_ctx, iface, &cfg, flags, ver);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed, exit
    }

    // Use aom_codec_peek_stream_info
    aom_codec_stream_info_t si = {0};
    si.is_annexb = 0; // Initialize required field
    res = aom_codec_peek_stream_info(iface, Data, Size, &si);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Stream info parsing failed, exit
    }

    // Decode the data
    res = aom_codec_decode(&codec_ctx, Data, Size, nullptr);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Decoding failed, exit
    }

    // Get stream info
    res = aom_codec_get_stream_info(&codec_ctx, &si);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Getting stream info failed, exit
    }

    // Get preview frame
    const aom_image_t *preview_frame = aom_codec_get_preview_frame(&codec_ctx);
    if (preview_frame == nullptr) {
        aom_codec_destroy(&codec_ctx);
        return 0; // No preview frame, exit
    }

    // Get decoded frames
    aom_codec_iter_t iter = nullptr;
    aom_image_t *img;
    while ((img = aom_codec_get_frame(&codec_ctx, &iter)) != nullptr) {
        // Process the images if needed
    }

    // Clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}