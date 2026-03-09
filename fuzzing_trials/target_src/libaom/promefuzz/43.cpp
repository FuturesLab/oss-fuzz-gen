// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER at aomcx.h:1922:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TILE_ROWS at aomcx.h:1965:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_TUNING at aomcx.h:1934:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ROI_MAP at aomcx.h:1898:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ACTIVEMAP at aomcx.h:1901:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_ACTIVEMAP at aomcx.h:2016:1 in aomcx.h
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

// Function to initialize codec context
static aom_codec_ctx_t initialize_codec() {
    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_enc_config_default(iface, &cfg, 0);
    aom_codec_enc_init(&codec, iface, &cfg, 0);
    return codec;
}

// Function to clean up codec context
static void cleanup_codec(aom_codec_ctx_t *codec) {
    aom_codec_destroy(codec);
}

// Function to handle aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER
static void test_get_last_quantizer(aom_codec_ctx_t *codec) {
    int quantizer;
    aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER(codec, 0, &quantizer);
}

// Function to handle aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
static void test_set_tile_rows(aom_codec_ctx_t *codec, unsigned int tile_rows) {
    aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(codec, 0, tile_rows);
}

// Function to handle aom_codec_control_typechecked_AOME_SET_TUNING
static void test_set_tuning(aom_codec_ctx_t *codec, int tuning) {
    aom_codec_control_typechecked_AOME_SET_TUNING(codec, 0, tuning);
}

// Function to handle aom_codec_control_typechecked_AOME_SET_ROI_MAP
static void test_set_roi_map(aom_codec_ctx_t *codec, aom_roi_map_t *roi_map) {
    aom_codec_control_typechecked_AOME_SET_ROI_MAP(codec, 0, roi_map);
}

// Function to handle aom_codec_control_typechecked_AOME_SET_ACTIVEMAP
static void test_set_activemap(aom_codec_ctx_t *codec, aom_active_map_t *active_map) {
    aom_codec_control_typechecked_AOME_SET_ACTIVEMAP(codec, 0, active_map);
}

// Function to handle aom_codec_control_typechecked_AV1E_GET_ACTIVEMAP
static void test_get_activemap(aom_codec_ctx_t *codec, aom_active_map_t *active_map) {
    aom_codec_control_typechecked_AV1E_GET_ACTIVEMAP(codec, 0, active_map);
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec = initialize_codec();

    unsigned int tile_rows = Data[0] % 64;
    test_set_tile_rows(&codec, tile_rows);

    int tuning = Data[0] % 3;
    test_set_tuning(&codec, tuning);

    aom_roi_map_t roi_map;
    roi_map.enabled = 1;
    roi_map.roi_map = (unsigned char*)malloc(Size);
    memcpy(roi_map.roi_map, Data, Size);
    roi_map.rows = Size / 4;
    test_set_roi_map(&codec, &roi_map);
    free(roi_map.roi_map);

    aom_active_map_t active_map;
    active_map.active_map = (unsigned char*)malloc(Size);
    memcpy(active_map.active_map, Data, Size);
    active_map.rows = Size / 16;
    test_set_activemap(&codec, &active_map);
    test_get_activemap(&codec, &active_map);
    free(active_map.active_map);

    test_get_last_quantizer(&codec);

    cleanup_codec(&codec);

    return 0;
}