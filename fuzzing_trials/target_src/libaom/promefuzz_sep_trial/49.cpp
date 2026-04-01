// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD at aomcx.h:1919:1 in aomcx.h
// aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER at aomcx.h:1922:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS at aomcx.h:2347:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS at aomcx.h:2004:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR at aomcx.h:2365:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT at aomcx.h:1940:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    std::memcpy(&codec_ctx, Data, sizeof(aom_codec_ctx_t));

    // Dummy variable to act as the argument for control functions
    int dummy_arg = 0;

    // Fuzz aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    if (Size > sizeof(aom_codec_ctx_t) + sizeof(int)) {
        unsigned int static_threshold = *reinterpret_cast<const unsigned int*>(Data + sizeof(aom_codec_ctx_t));
        aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD(&codec_ctx, 0, static_threshold);
    }

    // Fuzz aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER
    int last_quantizer = 0;
    aom_codec_control_typechecked_AOME_GET_LAST_QUANTIZER(&codec_ctx, 0, &last_quantizer);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS
    if (Size > sizeof(aom_codec_ctx_t) + 2 * sizeof(int)) {
        int quantizer_one_pass = *reinterpret_cast<const int*>(Data + sizeof(aom_codec_ctx_t) + sizeof(int));
        aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS(&codec_ctx, 0, quantizer_one_pass);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS
    if (Size > sizeof(aom_codec_ctx_t) + 3 * sizeof(int)) {
        int matrix_coefficients = *reinterpret_cast<const int*>(Data + sizeof(aom_codec_ctx_t) + 2 * sizeof(int));
        aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(&codec_ctx, 0, matrix_coefficients);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR
    if (Size > sizeof(aom_codec_ctx_t) + 4 * sizeof(int)) {
        int max_consec_frame_drop_cbr = *reinterpret_cast<const int*>(Data + sizeof(aom_codec_ctx_t) + 3 * sizeof(int));
        aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(&codec_ctx, 0, max_consec_frame_drop_cbr);
    }

    // Fuzz aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT
    if (Size > sizeof(aom_codec_ctx_t) + 5 * sizeof(int)) {
        int max_intra_bitrate_pct = *reinterpret_cast<const int*>(Data + sizeof(aom_codec_ctx_t) + 4 * sizeof(int));
        aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT(&codec_ctx, 0, max_intra_bitrate_pct);
    }

    return 0;
}