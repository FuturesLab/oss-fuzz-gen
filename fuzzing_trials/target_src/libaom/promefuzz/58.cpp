// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE at aomcx.h:1977:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA at aomcx.h:2164:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get the AV1 codec interface
    aom_codec_err_t res;

    // Initialize codec context
    res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Prepare to call target functions with varied inputs
    int control_type = Data[0] % 6; // Choose a control function based on the first byte
    int ctrl_value = Data[1] % 2; // Example control value for boolean-like settings
    int seq_level_idx = Data[1] % 32; // Example range for sequence level index
    int quantizer_value = Data[1] % 64; // Example range for quantizer
    int color_primary_value = Data[1] % 10; // Example range for color primaries

    switch (control_type) {
        case 0:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(&codec, 0, ctrl_value);
            break;
        case 1:
            aom_codec_control_typechecked_AV1E_SET_ERROR_RESILIENT_MODE(&codec, 0, ctrl_value);
            break;
        case 2:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(&codec, 0, ctrl_value);
            break;
        case 3:
            aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec, 0, seq_level_idx);
            break;
        case 4:
            aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS(&codec, 0, quantizer_value);
            break;
        case 5:
            aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec, 0, color_primary_value);
            break;
    }

    // Cleanup
    aom_codec_destroy(&codec);
    return 0;
}