// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_COMP_PRED at aomcx.h:2308:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2335:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH at aomcx.h:2305:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION at aomcx.h:2007:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID at aomcx.h:1907:1 in aomcx.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "aom/aomdx.h"
#include "aom/aom_frame_buffer.h"
#include "aom/aom_external_partition.h"
#include "aom/aom_encoder.h"
#include "aom/aom_codec.h"
#include "aom/aomcx.h"
#include "aom/aom_integer.h"
#include "aom/aom_image.h"
#include "aom/aom.h"
#include "aom/aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + 10) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_svc_ref_frame_comp_pred_t comp_pred;
    int color_primaries = static_cast<int>(Data[0]);
    int tx_size_search = static_cast<int>(Data[1]);
    int chroma_sample_position = static_cast<int>(Data[2]);
    int spatial_layer_id = static_cast<int>(Data[3]);
    int target_seq_level_idx;

    // Initialize codec context with dummy data
    codec_ctx.name = "dummy_codec";
    codec_ctx.err = static_cast<aom_codec_err_t>(0);
    codec_ctx.init_flags = 0;
    codec_ctx.priv = nullptr;

    // Prepare dummy data for comp_pred
    for (int i = 0; i < 3; ++i) {
        comp_pred.use_comp_pred[i] = static_cast<int>(Data[i + 4]);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_COMP_PRED
    aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_COMP_PRED(&codec_ctx, 0, &comp_pred);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
    aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, 0, color_primaries);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_TARGET_SEQ_LEVEL_IDX
    aom_codec_control_typechecked_AV1E_GET_TARGET_SEQ_LEVEL_IDX(&codec_ctx, 0, &target_seq_level_idx);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH
    aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH(&codec_ctx, 0, tx_size_search);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
    aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION(&codec_ctx, 0, chroma_sample_position);

    // Fuzz aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID
    aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(&codec_ctx, 0, spatial_layer_id);

    return 0;
}