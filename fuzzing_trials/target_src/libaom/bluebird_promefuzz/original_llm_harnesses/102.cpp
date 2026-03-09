// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
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
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aomcx.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_image.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_integer.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_ctx_t) + sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    codec_ctx.iface = iface;
    codec_ctx.priv = nullptr;

    int mode = Data[0] % 2; // Enable or disable mode
    int matrix_coefficients = Data[1] % 3; // Some arbitrary range
    int color_primaries = Data[2] % 3; // Some arbitrary range
    int enable_overlay = Data[3] % 2; // Enable or disable overlay
    int quantizer = Data[4] % 63; // Valid quantizer range
    aom_svc_params_t svc_params;
    svc_params.number_spatial_layers = Data[5] % 3 + 1; // Valid range [1, 3]

    // Initialize codec context
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Fuzz the functions with prepared data
    aom_codec_control(&codec_ctx, AV1E_SET_SCREEN_CONTENT_DETECTION_MODE, mode);
    aom_codec_control(&codec_ctx, AV1E_SET_MATRIX_COEFFICIENTS, matrix_coefficients);
    aom_codec_control(&codec_ctx, AV1E_SET_COLOR_PRIMARIES, color_primaries);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OVERLAY, enable_overlay);
    aom_codec_control(&codec_ctx, AV1E_SET_QUANTIZER_ONE_PASS, quantizer);
    aom_codec_control(&codec_ctx, AV1E_SET_SVC_PARAMS, &svc_params);

    // Clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}