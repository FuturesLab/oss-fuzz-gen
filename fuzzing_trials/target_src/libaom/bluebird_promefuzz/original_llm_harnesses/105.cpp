// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include "aomdx.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_encoder.h"
#include "aom_codec.h"
#include "aomcx.h"
#include "aom_integer.h"
#include "aom_image.h"
#include "aom.h"
#include "aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t* iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Prepare dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    if (!dummy_file.is_open()) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    // Test AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR
    int max_consec_frame_drop = *reinterpret_cast<const int*>(Data);
    aom_codec_control(&codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_consec_frame_drop);

    // Test AV1E_SET_S_FRAME_MODE
    int s_frame_mode = max_consec_frame_drop % 2;  // Use modulo to get a valid value
    aom_codec_control(&codec_ctx, AV1E_SET_S_FRAME_MODE, s_frame_mode);

    // Test AV1E_SET_MATRIX_COEFFICIENTS
    int matrix_coefficients = (max_consec_frame_drop >> 1) % 8;  // Use a smaller range
    aom_codec_control(&codec_ctx, AV1E_SET_MATRIX_COEFFICIENTS, matrix_coefficients);

    // Test AV1E_SET_ENABLE_OVERLAY
    int enable_overlay = s_frame_mode;  // Reuse s_frame_mode for enable/disable
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OVERLAY, enable_overlay);

    // Test AV1E_SET_QUANTIZER_ONE_PASS
    int quantizer = (max_consec_frame_drop >> 2) % 64;  // Use a range suitable for quantizer
    aom_codec_control(&codec_ctx, AV1E_SET_QUANTIZER_ONE_PASS, quantizer);

    // Test AV1E_SET_SVC_PARAMS
    aom_svc_params_t svc_params;
    svc_params.number_spatial_layers = (max_consec_frame_drop % 3) + 1;  // Valid range for layers
    for (int i = 0; i < AOM_MAX_LAYERS; ++i) {
        svc_params.max_quantizers[i] = quantizer;
    }
    aom_codec_control(&codec_ctx, AV1E_SET_SVC_PARAMS, &svc_params);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}