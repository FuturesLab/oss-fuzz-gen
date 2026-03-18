// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <aom/aom.h>
}

static void initialize_codec(aom_codec_ctx_t &codec_ctx, aom_codec_iface_t *iface) {
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        // Handle initialization error
    }
}

static void destroy_codec(aom_codec_ctx_t &codec_ctx) {
    aom_codec_err_t res = aom_codec_destroy(&codec_ctx);
    if (res != AOM_CODEC_OK) {
        // Handle destruction error
    }
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    initialize_codec(codec_ctx, iface);

    int param = *reinterpret_cast<const int*>(Data);

    // Fuzz aom_codec_control using the correct function signature
    aom_codec_control(&codec_ctx, AOME_SET_ENABLEAUTOALTREF, param);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_LOW_COMPLEXITY_DECODE, param);
    aom_codec_control(&codec_ctx, AV1E_SET_DV_COST_UPD_FREQ, param);
    aom_codec_control(&codec_ctx, AV1E_SET_MIN_GF_INTERVAL, param);
    aom_codec_control(&codec_ctx, AV1E_SET_DISABLE_TRELLIS_QUANT, param);
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OBMC, param);

    destroy_codec(codec_ctx);

    return 0;
}