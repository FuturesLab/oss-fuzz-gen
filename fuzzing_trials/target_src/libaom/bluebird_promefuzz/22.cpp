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
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aomcx.h"
#include "/src/aom/aom/aom_encoder.h"

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res = aom_codec_enc_config_default(iface, &cfg, 0);

    if (res != AOM_CODEC_OK) return 0;

    res = aom_codec_enc_init(&codec, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Fuzz aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE
    int s_frame_mode = Data[0] % 2;
    aom_codec_control(&codec, AV1E_SET_S_FRAME_MODE, s_frame_mode);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX
    int target_seq_level_idx = Data[0] % 32;
    aom_codec_control(&codec, AV1E_SET_TARGET_SEQ_LEVEL_IDX, target_seq_level_idx);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY
    int enable_overlay = Data[0] % 2;
    aom_codec_control(&codec, AV1E_SET_ENABLE_OVERLAY, enable_overlay);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS
    int quantizer = Data[0] % 64;
    aom_codec_control(&codec, AV1E_SET_QUANTIZER_ONE_PASS, quantizer);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS
    int num_operating_points;
    aom_codec_control(&codec, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SVC_PARAMS
    aom_svc_params_t svc_params;
    memset(&svc_params, 0, sizeof(svc_params));
    svc_params.number_spatial_layers = Data[0] % 3 + 1;
    aom_codec_control(&codec, AV1E_SET_SVC_PARAMS, &svc_params);

    aom_codec_destroy(&codec);
    return 0;
}