// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_INTRA_DCT_ONLY at aomcx.h:2218:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION at aomcx.h:2007:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR at aomcx.h:2377:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_GOP_INFO at aomcx.h:2393:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
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
#include <cstdint>
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec;
    std::memcpy(&codec, Data, sizeof(aom_codec_ctx_t));

    int control_id = 0;
    int value = 0;

    // Fuzz aom_codec_control_typechecked_AV1E_SET_INTRA_DCT_ONLY
    std::memcpy(&value, Data + sizeof(aom_codec_ctx_t), sizeof(int));
    if (aom_codec_control_typechecked_AV1E_SET_INTRA_DCT_ONLY(&codec, control_id, value) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
    std::memcpy(&value, Data + sizeof(aom_codec_ctx_t), sizeof(int));
    if (aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION(&codec, control_id, value) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR
    std::memcpy(&value, Data + sizeof(aom_codec_ctx_t), sizeof(int));
    if (aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR(&codec, control_id, value) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_GET_GOP_INFO
    aom_gop_info_t gop_info;
    if (aom_codec_control_typechecked_AV1E_GET_GOP_INFO(&codec, control_id, &gop_info) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
    std::memcpy(&value, Data + sizeof(aom_codec_ctx_t), sizeof(int));
    if (aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec, control_id, value) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX
    std::memcpy(&value, Data + sizeof(aom_codec_ctx_t), sizeof(int));
    if (aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec, control_id, value) != AOM_CODEC_OK) {
        return 0;
    }

    return 0;
}