// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG at aomcx.h:2264:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS at aomcx.h:2004:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR at aomcx.h:2365:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA at aomcx.h:2302:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS at aomcx.h:2001:1 in aomcx.h
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
#include <cstring>
#include <iostream>
#include <fstream>
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

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Prepare codec context
    aom_codec_ctx_t codec_ctx;
    std::memset(&codec_ctx, 0, sizeof(aom_codec_ctx_t));

    // Prepare dummy file if needed
    std::ofstream dummy_file("./dummy_file");
    if (dummy_file.is_open()) {
        dummy_file.write(reinterpret_cast<const char*>(Data), Size);
        dummy_file.close();
    }

    // Initialize codec context with a valid interface
    codec_ctx.iface = aom_codec_av1_cx();
    if (!codec_ctx.iface) {
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE
    if (Size > sizeof(aom_codec_ctx_t)) {
        int enable_palette = Data[sizeof(aom_codec_ctx_t)] % 2;
        aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(&codec_ctx, 0, enable_palette);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG
    if (Size > sizeof(aom_codec_ctx_t) + 1) {
        aom_svc_ref_frame_config_t ref_frame_config;
        std::memset(&ref_frame_config, 0, sizeof(ref_frame_config));
        aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG(&codec_ctx, 0, &ref_frame_config);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS
    if (Size > sizeof(aom_codec_ctx_t) + 2) {
        int matrix_coefficients = Data[sizeof(aom_codec_ctx_t) + 2];
        aom_codec_control_typechecked_AV1E_SET_MATRIX_COEFFICIENTS(&codec_ctx, 0, matrix_coefficients);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR
    if (Size > sizeof(aom_codec_ctx_t) + 3) {
        int max_consec_frame_drop = Data[sizeof(aom_codec_ctx_t) + 3];
        aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(&codec_ctx, 0, max_consec_frame_drop);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA
    if (Size > sizeof(aom_codec_ctx_t) + 4) {
        int enable_directional_intra = Data[sizeof(aom_codec_ctx_t) + 4] % 2;
        aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(&codec_ctx, 0, enable_directional_intra);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS
    if (Size > sizeof(aom_codec_ctx_t) + 5) {
        int transfer_characteristics = Data[sizeof(aom_codec_ctx_t) + 5];
        aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS(&codec_ctx, 0, transfer_characteristics);
    }

    // Cleanup and return
    aom_codec_destroy(&codec_ctx);
    return 0;
}