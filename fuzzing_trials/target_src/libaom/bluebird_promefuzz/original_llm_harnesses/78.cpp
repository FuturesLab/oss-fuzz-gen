// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AOME_SET_ROI_MAP at aomcx.h:1898:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE at aomcx.h:2362:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_TUNING at aomcx.h:1934:1 in aomcx.h
// aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER at aomcx.h:1922:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TILE_ROWS at aomcx.h:1965:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD at aomcx.h:1919:1 in aomcx.h
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
#include "aom.h"
#include "aom_codec.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    codec_ctx.name = "Test Codec";
    codec_ctx.iface = nullptr;
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.priv = nullptr;

    // Initialize ROI map
    aom_roi_map_t roi_map;
    roi_map.enabled = 1;
    roi_map.roi_map = new unsigned char[Size];
    roi_map.rows = Size / 2;
    roi_map.delta_q[0] = 10;
    roi_map.delta_qp_enabled = 1;

    // Define control IDs
    int ctrl_id_set_roi_map = AOME_SET_ROI_MAP;
    int ctrl_id_set_svc_frame_drop_mode = AV1E_SET_SVC_FRAME_DROP_MODE;
    int ctrl_id_set_tuning = AOME_SET_TUNING;
    int ctrl_id_get_last_quantizer = AOME_GET_LAST_QUANTIZER;
    int ctrl_id_set_tile_rows = AV1E_SET_TILE_ROWS;
    int ctrl_id_set_static_threshold = AOME_SET_STATIC_THRESHOLD;

    // Invoke aom_codec_control_typechecked_AOME_SET_ROI_MAP
    aom_codec_err_t res = aom_codec_control_typechecked_AOME_SET_ROI_MAP(&codec_ctx, ctrl_id_set_roi_map, &roi_map);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE
    int frame_drop_mode = Data[0] % 3; // Simple mode selection
    res = aom_codec_control_typechecked_AV1E_SET_SVC_FRAME_DROP_MODE(&codec_ctx, ctrl_id_set_svc_frame_drop_mode, frame_drop_mode);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AOME_SET_TUNING
    int tuning = Data[1] % 4; // Simple tuning selection
    res = aom_codec_control_typechecked_AOME_SET_TUNING(&codec_ctx, ctrl_id_set_tuning, tuning);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER
    int last_quantizer;
    res = aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER(&codec_ctx, ctrl_id_get_last_quantizer, &last_quantizer);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
    int tile_rows = Data[2] % 4; // Simple tile row selection
    res = aom_codec_control_typechecked_AV1E_SET_TILE_ROWS(&codec_ctx, ctrl_id_set_tile_rows, tile_rows);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    int static_threshold = Data[3] % 100; // Simple static threshold
    res = aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD(&codec_ctx, ctrl_id_set_static_threshold, static_threshold);
    if (res != AOM_CODEC_OK) {
        delete[] roi_map.roi_map;
        return 0;
    }

    // Clean up
    delete[] roi_map.roi_map;
    return 0;
}