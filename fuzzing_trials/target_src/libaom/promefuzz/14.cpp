// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
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
#include <cstdlib>
#include <cstring>
#include "aom/aom_codec.h"
#include "aom/aom_encoder.h"
#include "aom/aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    int enable_cfl_intra = Data[0] % 2; // 0 or 1
    int max_consec_frame_drop_cbr = Data[0];
    int enable_palette = Data[0] % 2; // 0 or 1
    int matrix_coefficients = Data[0];
    int quantizer_one_pass = Data[0];

    // Initialize codec
    res = aom_codec_enc_init(&codec, aom_codec_av1_cx(), NULL, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Set ENABLE_CFL_INTRA
    aom_codec_control(&codec, AV1E_SET_ENABLE_CFL_INTRA, enable_cfl_intra);

    // Set MAX_CONSEC_FRAME_DROP_CBR
    aom_codec_control(&codec, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_consec_frame_drop_cbr);

    // Set ENABLE_PALETTE
    aom_codec_control(&codec, AV1E_SET_ENABLE_PALETTE, enable_palette);

    // Set MATRIX_COEFFICIENTS
    aom_codec_control(&codec, AV1E_SET_MATRIX_COEFFICIENTS, matrix_coefficients);

    // Get HIGH_MOTION_CONTENT_SCREEN_RTC
    int high_motion_content;
    aom_codec_control(&codec, AV1E_GET_HIGH_MOTION_CONTENT_SCREEN_RTC, &high_motion_content);

    // Set QUANTIZER_ONE_PASS
    aom_codec_control(&codec, AV1E_SET_QUANTIZER_ONE_PASS, quantizer_one_pass);

    // Destroy codec
    aom_codec_destroy(&codec);

    return 0;
}