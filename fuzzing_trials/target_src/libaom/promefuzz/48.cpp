// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE at aomcx.h:2043:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_FP_MT at aomcx.h:2329:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL at aomcx.h:1968:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL at aomcx.h:2010:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS at aomcx.h:2387:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
// aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE at aomcx.h:1995:1 in aomcx.h
// aom_codec_err_to_string at aom_codec.c:36:13 in aom_codec.h
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
#include "aom_encoder.h"
#include "aomcx.h"

static bool init_codec(aom_codec_ctx_t *codec, aom_codec_iface_t *iface) {
    aom_codec_err_t res = aom_codec_enc_init(codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to initialize codec: %s\n", aom_codec_err_to_string(res));
        return false;
    }
    return true;
}

static void cleanup_codec(aom_codec_ctx_t *codec) {
    aom_codec_err_t res = aom_codec_destroy(codec);
    if (res != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to destroy codec: %s\n", aom_codec_err_to_string(res));
    }
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    if (!init_codec(&codec, iface)) {
        return 0; // Exit gracefully if codec initialization fails
    }

    int param = 0;
    memcpy(&param, Data, sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE
    aom_codec_err_t res1 = aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE(&codec, AV1E_SET_FORCE_VIDEO_MODE, param);
    if (res1 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_FORCE_VIDEO_MODE: %s\n", aom_codec_err_to_string(res1));
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FP_MT
    aom_codec_err_t res2 = aom_codec_control_typechecked_AV1E_SET_FP_MT(&codec, AV1E_SET_FP_MT, param);
    if (res2 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_FP_MT: %s\n", aom_codec_err_to_string(res2));
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL
    aom_codec_err_t res3 = aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(&codec, AV1E_SET_ENABLE_TPL_MODEL, param);
    if (res3 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_ENABLE_TPL_MODEL: %s\n", aom_codec_err_to_string(res3));
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL
    aom_codec_err_t res4 = aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec, AV1E_SET_MIN_GF_INTERVAL, param);
    if (res4 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_MIN_GF_INTERVAL: %s\n", aom_codec_err_to_string(res4));
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS
    aom_codec_err_t res5 = aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS(&codec, AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS, param);
    if (res5 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS: %s\n", aom_codec_err_to_string(res5));
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE
    aom_codec_err_t res6 = aom_codec_control_typechecked_AV1E_SET_CDF_UPDATE_MODE(&codec, AV1E_SET_CDF_UPDATE_MODE, param);
    if (res6 != AOM_CODEC_OK) {
        fprintf(stderr, "Error in AV1E_SET_CDF_UPDATE_MODE: %s\n", aom_codec_err_to_string(res6));
    }

    cleanup_codec(&codec);
    return 0;
}