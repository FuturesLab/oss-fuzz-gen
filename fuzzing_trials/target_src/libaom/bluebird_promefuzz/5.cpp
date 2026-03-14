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
#include <exception>
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 6) {
        return 0;  // Not enough data to proceed
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;

    if (aom_codec_enc_config_default(iface, &cfg, 0)) {
        return 0;  // Failed to get default config
    }

    if (aom_codec_enc_init(&codec_ctx, iface, &cfg, 0)) {
        return 0;  // Failed to initialize codec
    }

    try {
        int enable_auto_alt_ref = Data[0] % 2;
        aom_codec_control(&codec_ctx, AOME_SET_ENABLEAUTOALTREF, enable_auto_alt_ref);

        aom_scaling_mode_t scaling_mode;
        scaling_mode.h_scaling_mode = static_cast<AOM_SCALING_MODE>(Data[1] % 9);
        aom_codec_control(&codec_ctx, AOME_SET_SCALEMODE, &scaling_mode);

        int num_spatial_layers = Data[2] % 4;
        aom_codec_control(&codec_ctx, AOME_SET_NUMBER_SPATIAL_LAYERS, num_spatial_layers);

        int tuning = Data[3] % 3;
        aom_codec_control(&codec_ctx, AOME_SET_TUNING, tuning);

        int spatial_layer_id = Data[4] % 4;
        aom_codec_control(&codec_ctx, AOME_SET_SPATIAL_LAYER_ID, spatial_layer_id);

        int max_gf_interval = Data[5] % 100;
        aom_codec_control(&codec_ctx, AV1E_SET_MAX_GF_INTERVAL, max_gf_interval);
    } catch (const std::exception &e) {
        // Handle any exceptions that might be thrown by the codec control functions
    }

    aom_codec_destroy(&codec_ctx);
    return 0;
}