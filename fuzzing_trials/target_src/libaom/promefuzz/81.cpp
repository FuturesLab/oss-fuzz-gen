// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aom.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_enc_cfg_t)) {
        return 0;
    }

    // Prepare encoder configuration
    aom_codec_enc_cfg_t cfg;
    memcpy(&cfg, Data, sizeof(cfg));

    // Initialize codec context
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    // Initialize encoder interface
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) {
        return 0;
    }

    // Initialize the encoder
    aom_codec_err_t res = aom_codec_enc_init_ver(&codec, iface, &cfg, 0, AOM_ENCODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Set active map
    aom_active_map_t active_map;
    active_map.rows = 1;
    active_map.active_map = new unsigned char[1];
    active_map.active_map[0] = 1;
    res = aom_codec_control(&codec, AOME_SET_ACTIVEMAP, &active_map);
    delete[] active_map.active_map;

    // Set ROI map
    aom_roi_map_t roi_map;
    roi_map.enabled = 1;
    roi_map.rows = 1;
    roi_map.roi_map = new unsigned char[1];
    roi_map.roi_map[0] = 0;
    res = aom_codec_control(&codec, AOME_SET_ROI_MAP, &roi_map);
    delete[] roi_map.roi_map;

    // Get last quantizer
    int last_quantizer;
    res = aom_codec_control(&codec, AOME_GET_LAST_QUANTIZER, &last_quantizer);

    // Set tile rows
    int tile_rows = 2;
    res = aom_codec_control(&codec, AV1E_SET_TILE_ROWS, tile_rows);

    // Get active map
    aom_active_map_t retrieved_active_map;
    res = aom_codec_control(&codec, AV1E_GET_ACTIVEMAP, &retrieved_active_map);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}