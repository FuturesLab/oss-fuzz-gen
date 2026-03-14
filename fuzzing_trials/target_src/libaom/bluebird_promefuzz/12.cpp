#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "stdint.h"
#include "stddef.h"
#include <fstream>
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t res;

    // Assume the interface is for AV1 encoder
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    // Initialize encoder configuration
    aom_codec_enc_cfg_t cfg;
    res = aom_codec_enc_config_default(iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Initialize codec
    res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Prepare a dummy file if needed
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Extract an integer from the input data
    int control_value = *reinterpret_cast<const int*>(Data);

    // Fuzz each target function with extracted control_value
    aom_codec_control(&codec_ctx, AV1E_SET_NOISE_SENSITIVITY, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_FP_MT_UNIT_TEST, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_MIN_GF_INTERVAL, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_AUTO_INTRA_TOOLS_OFF, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_COLUMNS, control_value);
    aom_codec_control(&codec_ctx, AV1E_SET_CDF_UPDATE_MODE, control_value);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}