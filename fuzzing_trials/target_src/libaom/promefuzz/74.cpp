// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>

extern "C" {
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
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;  // Ensure there's enough data

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;

    // Initialize the codec
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }
    if (aom_codec_enc_init(&codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Extract integer values from the input data
    int sharpness = Data[0] % 8;  // Sharpness levels typically range from 0 to 7
    int arnr_strength = Data[1] % 6;  // ARNR strength range example
    int enable_auto_alt_ref = Data[2] % 2;  // Boolean value
    int enable_auto_bwd_ref = Data[3] % 2;  // Boolean value
    int cq_level = Data[4] % 64;  // Example range for CQ level
    int arnr_max_frames = Data[5] % 15;  // Example range for max frames

    // Set sharpness
    aom_codec_control(&codec_ctx, AOME_SET_SHARPNESS, sharpness);

    // Set ARNR strength
    aom_codec_control(&codec_ctx, AOME_SET_ARNR_STRENGTH, arnr_strength);

    // Enable or disable auto alt ref
    aom_codec_control(&codec_ctx, AOME_SET_ENABLEAUTOALTREF, enable_auto_alt_ref);

    // Enable or disable auto bwd ref
    aom_codec_control(&codec_ctx, AOME_SET_ENABLEAUTOBWDREF, enable_auto_bwd_ref);

    // Set CQ level
    aom_codec_control(&codec_ctx, AOME_SET_CQ_LEVEL, cq_level);

    // Set ARNR max frames
    aom_codec_control(&codec_ctx, AOME_SET_ARNR_MAXFRAMES, arnr_max_frames);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}