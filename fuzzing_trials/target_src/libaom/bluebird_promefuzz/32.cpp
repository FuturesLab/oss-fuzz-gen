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
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"
#include "aom/aomdx.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "aom/aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(aom_scaling_mode_t) + sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.name = "test_codec";

    aom_scaling_mode_t scaling_mode;
    memcpy(&scaling_mode, Data, sizeof(scaling_mode));
    Data += sizeof(scaling_mode);
    Size -= sizeof(scaling_mode);

    int param = 0;
    memcpy(&param, Data, sizeof(param));
    Data += sizeof(param);
    Size -= sizeof(param);

    // Use a dummy control ID for demonstration purposes
    const int dummy_ctrl_id = 0;

    // Fuzz aom_codec_control_typechecked_AOME_SET_TUNING
    aom_codec_control_typechecked_AOME_SET_TUNING(&codec_ctx, dummy_ctrl_id, param);

    // Fuzz aom_codec_control_typechecked_AOME_SET_SCALEMODE
    aom_codec_control_typechecked_AOME_SET_SCALEMODE(&codec_ctx, dummy_ctrl_id, &scaling_mode);

    // Fuzz aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES
    aom_codec_control_typechecked_AOME_SET_ARNR_MAXFRAMES(&codec_ctx, dummy_ctrl_id, param);

    // Fuzz aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS
    aom_codec_control_typechecked_AOME_SET_NUMBER_SPATIAL_LAYERS(&codec_ctx, dummy_ctrl_id, param);

    // Fuzz aom_codec_control_typechecked_AOME_SET_CQ_LEVEL
    aom_codec_control_typechecked_AOME_SET_CQ_LEVEL(&codec_ctx, dummy_ctrl_id, param);

    // Fuzz aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID
    aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(&codec_ctx, dummy_ctrl_id, param);

    return 0;
}