// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <cstring>
#include "aom/aom_codec.h"
#include "aom/aom_encoder.h"
#include "aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 6) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res;

    // Initialize codec
    res = aom_codec_enc_config_default(iface, &cfg, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Extract integer values from input data
    unsigned int tile_rows = Data[0] % 64; // Example constraint
    unsigned int tile_columns = Data[1] % 64; // Example constraint
    unsigned int noise_sensitivity = Data[2] % 100; // Example constraint
    unsigned int disable_trellis_quant = Data[3] % 2; // Boolean flag
    unsigned int auto_intra_tools_off = Data[4] % 2; // Boolean flag
    unsigned int fp_mt_unit_test = Data[5] % 2; // Boolean flag

    // Fuzz the target API functions
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_ROWS, tile_rows);
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_COLUMNS, tile_columns);
    aom_codec_control(&codec_ctx, AV1E_SET_NOISE_SENSITIVITY, noise_sensitivity);
    aom_codec_control(&codec_ctx, AV1E_SET_DISABLE_TRELLIS_QUANT, disable_trellis_quant);
    aom_codec_control(&codec_ctx, AV1E_SET_AUTO_INTRA_TOOLS_OFF, auto_intra_tools_off);
    aom_codec_control(&codec_ctx, AV1E_SET_FP_MT_UNIT_TEST, fp_mt_unit_test);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}