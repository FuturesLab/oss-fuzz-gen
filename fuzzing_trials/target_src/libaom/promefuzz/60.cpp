// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION at aomcx.h:2007:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS at aomcx.h:2004:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS at aomcx.h:2347:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
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
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Assuming AV1 encoder is used

    // Initialize codec
    if (aom_codec_enc_init(&codec, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    // Prepare inputs from fuzz data
    int chroma_sample_position = Data[0] % 3; // Example: Limit to 3 possible values
    int enable_palette = Data[1] % 2; // 0 or 1
    int matrix_coefficients = Data[2] % 6; // Example: Limit to 6 possible values
    int target_seq_level_idx = Data[3] % 32; // Example: Limit to 32 possible values
    int quantizer = Data[4] % 64; // Example: Limit to 64 possible values
    int color_primaries = Data[5] % 10; // Example: Limit to 10 possible values

    // Invoke target functions with proper arguments
    aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION(&codec, 0, chroma_sample_position);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(&codec, 0, enable_palette);
    aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(&codec, 0, matrix_coefficients);
    aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec, 0, target_seq_level_idx);
    aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS(&codec, 0, quantizer);
    aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec, 0, color_primaries);

    // Cleanup
    aom_codec_destroy(&codec);
    return 0;
}