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
#include <cassert>
#include "/src/aom/aom/aom_codec.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0};
    aom_codec_flags_t flags = 0;
    int ver = AOM_DECODER_ABI_VERSION;

    // Initialize the codec
    if (aom_codec_dec_init_ver(&codec_ctx, iface, &cfg, flags, ver) != AOM_CODEC_OK) {
        return 0;
    }

    // Decode data
    if (aom_codec_decode(&codec_ctx, Data, Size, nullptr) != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Get frame
    aom_codec_iter_t iter = nullptr;
    aom_image_t *img = nullptr;
    while ((img = aom_codec_get_frame(&codec_ctx, &iter)) != nullptr) {
        // Process the frame (e.g., validate or analyze image data)
    }

    // Get stream info
    aom_codec_stream_info_t stream_info = {0};
    if (aom_codec_get_stream_info(&codec_ctx, &stream_info) == AOM_CODEC_OK) {
        // Use stream info (e.g., width and height)
    }

    // Peek stream info
    if (Size >= 4) { // Ensure there's enough data to peek
        aom_codec_stream_info_t peek_info = {0};

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of aom_codec_peek_stream_info
        if (aom_codec_peek_stream_info(iface, Data, AOM_MAX_TILE_COLS, &peek_info) == AOM_CODEC_OK) {
        // End mutation: Producer.REPLACE_ARG_MUTATOR


            // Use peek info
        }
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}