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
#include <cstring>
#include "aom.h"
#include "aomcx.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomdx.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's enough data

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res = aom_codec_enc_config_default(iface, &cfg, 0);

    if (res != AOM_CODEC_OK) return 0;

    res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Fuzz aom_codec_control_typechecked_AOME_USE_REFERENCE
    int ref_frame_index = Data[0] % 8; // Ensure index is within a valid range
    aom_codec_control(&codec_ctx, AOME_USE_REFERENCE, ref_frame_index);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_TARGET_SEQ_LEVEL_IDX
    int level_idx;
    aom_codec_control(&codec_ctx, AV1E_GET_TARGET_SEQ_LEVEL_IDX, &level_idx);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG
    aom_svc_ref_frame_config_t ref_config;
    memset(&ref_config, 0, sizeof(ref_config));
    ref_config.reference[0] = Data[0] % 2;
    ref_config.refresh[0] = Data[0] % 2;
    aom_codec_control(&codec_ctx, AV1E_SET_SVC_REF_FRAME_CONFIG, &ref_config);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
    int chroma_sample_position = Data[0] % 3; // Assuming 3 valid positions
    aom_codec_control(&codec_ctx, AV1E_SET_CHROMA_SAMPLE_POSITION, chroma_sample_position);

    // Fuzz aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS
    int num_spatial_layers = Data[0] % 4 + 1; // Assuming 1 to 4 layers
    aom_codec_control(&codec_ctx, AOME_SET_NUMBER_SPATIAL_LAYERS, num_spatial_layers);

    // Fuzz aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID
    int spatial_layer_id = Data[0] % num_spatial_layers;
    aom_codec_control(&codec_ctx, AOME_SET_SPATIAL_LAYER_ID, spatial_layer_id);

    aom_codec_destroy(&codec_ctx);
    return 0;
}