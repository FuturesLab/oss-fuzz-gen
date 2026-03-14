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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(aom_codec_enc_cfg_t)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_enc_cfg_t enc_cfg;
    std::memcpy(&codec_ctx, Data, sizeof(aom_codec_ctx_t));
    std::memcpy(&enc_cfg, Data + sizeof(aom_codec_ctx_t), sizeof(aom_codec_enc_cfg_t));

    // Initialize codec context with dummy values
    codec_ctx.name = "dummy_codec";
    codec_ctx.iface = nullptr;
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.priv = nullptr;

    // Initialize encoder configuration with dummy values
    enc_cfg.g_usage = 0;
    enc_cfg.g_bit_depth = AOM_BITS_8;
    enc_cfg.g_timebase.num = 1;
    enc_cfg.g_error_resilient = 0;
    enc_cfg.g_pass = AOM_RC_ONE_PASS;
    enc_cfg.rc_superres_mode = static_cast<aom_superres_mode>(0);
    enc_cfg.rc_end_usage = AOM_VBR;
    enc_cfg.rc_twopass_stats_in.buf = nullptr;
    enc_cfg.fwd_kf_enabled = 0;
    enc_cfg.kf_mode = AOM_KF_AUTO;
    enc_cfg.encoder_cfg.init_by_cfg_file = 0;

    // Test aom_codec_enc_config_set
    aom_codec_err_t err = aom_codec_enc_config_set(&codec_ctx, &enc_cfg);
    if (err != AOM_CODEC_OK) {
        std::cerr << "Error setting encoder config: " << err << std::endl;
    }

    // Test aom_codec_get_global_headers
    aom_fixed_buf_t *global_headers = aom_codec_get_global_headers(&codec_ctx);
    if (global_headers) {
        free(global_headers->buf);
        free(global_headers);
    }

    // Test aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT
    int max_intra_bitrate_pct = 100;
    err = aom_codec_control(&codec_ctx, AOME_SET_MAX_INTRA_BITRATE_PCT, max_intra_bitrate_pct);
    if (err != AOM_CODEC_OK) {
        std::cerr << "Error setting max intra bitrate pct: " << err << std::endl;
    }

    // Test aom_codec_control_typechecked_AOME_SET_ROI_MAP
    aom_roi_map_t roi_map;
    roi_map.enabled = 1;
    roi_map.roi_map = nullptr;
    roi_map.rows = 0;
    roi_map.delta_q[0] = 0;
    roi_map.delta_qp_enabled = 0;
    err = aom_codec_control(&codec_ctx, AOME_SET_ROI_MAP, &roi_map);
    if (err != AOM_CODEC_OK) {
        std::cerr << "Error setting ROI map: " << err << std::endl;
    }

    // Test aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE
    int force_video_mode = 1;
    err = aom_codec_control(&codec_ctx, AV1E_SET_FORCE_VIDEO_MODE, force_video_mode);
    if (err != AOM_CODEC_OK) {
        std::cerr << "Error setting force video mode: " << err << std::endl;
    }

    // Test aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER
    int last_quantizer = 0;
    err = aom_codec_control(&codec_ctx, AOME_GET_LAST_QUANTIZER, &last_quantizer);
    if (err != AOM_CODEC_OK) {
        std::cerr << "Error getting last quantizer: " << err << std::endl;
    }

    return 0;
}