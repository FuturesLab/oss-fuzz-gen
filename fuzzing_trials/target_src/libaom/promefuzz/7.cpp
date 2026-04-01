// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
#include <iostream>
#include <cstring>
#include <cstdint>
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
}

static void init_codec_context(aom_codec_ctx_t &codec_ctx) {
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.name = "AV1 Codec";
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;
}

static void cleanup_codec_context(aom_codec_ctx_t &codec_ctx) {
    if (codec_ctx.iface) {
        aom_codec_destroy(&codec_ctx);
    }
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    aom_codec_ctx_t codec_ctx;
    init_codec_context(codec_ctx);

    int enable_obmc = Data[0] % 2;
    int deltaq_strength = Data[1] % 256;
    int aq_mode = Data[2] % 4;
    int enable_adaptive_sharpness = Data[3] % 2;
    int enable_restoration = Data[4] % 2;
    int cdf_update_mode = Data[5] % 3;

    aom_codec_err_t res;

    res = aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OBMC, enable_obmc);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set OBMC: " << aom_codec_err_to_string(res) << std::endl;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_DELTAQ_STRENGTH, deltaq_strength);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set DeltaQ Strength: " << aom_codec_err_to_string(res) << std::endl;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_AQ_MODE, aq_mode);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set AQ Mode: " << aom_codec_err_to_string(res) << std::endl;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS, enable_adaptive_sharpness);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set Adaptive Sharpness: " << aom_codec_err_to_string(res) << std::endl;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_RESTORATION, enable_restoration);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set Restoration: " << aom_codec_err_to_string(res) << std::endl;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_CDF_UPDATE_MODE, cdf_update_mode);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Failed to set CDF Update Mode: " << aom_codec_err_to_string(res) << std::endl;
    }

    cleanup_codec_context(codec_ctx);
    return 0;
}