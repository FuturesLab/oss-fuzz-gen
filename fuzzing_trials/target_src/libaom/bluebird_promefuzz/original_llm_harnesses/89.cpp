// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_config_set at aom_encoder.c:298:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY at aomcx.h:2170:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ROI_MAP at aomcx.h:1898:1 in aomcx.h
// aom_codec_get_global_headers at aom_encoder.c:281:18 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_TILE_ROWS at aomcx.h:1965:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
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
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

static aom_codec_ctx_t* initialize_codec_context() {
    aom_codec_ctx_t *ctx = new aom_codec_ctx_t;
    memset(ctx, 0, sizeof(aom_codec_ctx_t));
    return ctx;
}

static aom_codec_enc_cfg_t* initialize_codec_enc_cfg() {
    aom_codec_enc_cfg_t *cfg = new aom_codec_enc_cfg_t;
    memset(cfg, 0, sizeof(aom_codec_enc_cfg_t));
    return cfg;
}

static aom_roi_map_t* initialize_roi_map() {
    aom_roi_map_t *roi_map = new aom_roi_map_t;
    memset(roi_map, 0, sizeof(aom_roi_map_t));
    return roi_map;
}

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t *ctx = initialize_codec_context();
    aom_codec_enc_cfg_t *cfg = initialize_codec_enc_cfg();
    aom_roi_map_t *roi_map = initialize_roi_map();

    int control_value = *(reinterpret_cast<const int*>(Data));
    Data += sizeof(int);
    Size -= sizeof(int);

    aom_codec_err_t res;

    // Fuzz aom_codec_enc_config_set
    if (Size >= sizeof(aom_codec_enc_cfg_t)) {
        memcpy(cfg, Data, sizeof(aom_codec_enc_cfg_t));
        res = aom_codec_enc_config_set(ctx, cfg);
        if (res != AOM_CODEC_OK) {
            std::cerr << "aom_codec_enc_config_set error: " << res << std::endl;
        }
        Data += sizeof(aom_codec_enc_cfg_t);
        Size -= sizeof(aom_codec_enc_cfg_t);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(ctx, AV1E_SET_ENABLE_OVERLAY, control_value);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY error: " << res << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AOME_SET_ROI_MAP
    res = aom_codec_control_typechecked_AOME_SET_ROI_MAP(ctx, AOME_SET_ROI_MAP, roi_map);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AOME_SET_ROI_MAP error: " << res << std::endl;
    }

    // Fuzz aom_codec_get_global_headers
    aom_fixed_buf_t *global_headers = aom_codec_get_global_headers(ctx);
    if (global_headers) {
        free(global_headers->buf);
        free(global_headers);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
    res = aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(ctx, AV1E_SET_TILE_ROWS, control_value);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_TILE_ROWS error: " << res << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(ctx, AV1E_SET_ENABLE_PALETTE, control_value);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE error: " << res << std::endl;
    }

    delete ctx;
    delete cfg;
    delete roi_map;

    return 0;
}