// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_PARAMS at aomcx.h:2259:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY at aomcx.h:2170:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR at aomcx.h:2365:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL at aomcx.h:2317:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA at aomcx.h:2302:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS at aomcx.h:2347:1 in aomcx.h
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
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 6) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;

    // Initialize SVC parameters
    aom_svc_params_t svc_params;
    memset(&svc_params, 0, sizeof(svc_params));
    svc_params.number_spatial_layers = 1 + (Data[0] % 3);

    // Set SVC parameters
    if (aom_codec_control_typechecked_AV1E_SET_SVC_PARAMS(&codec_ctx, AV1E_SET_SVC_PARAMS, &svc_params) != AOM_CODEC_OK) {
        return 0;
    }

    // Enable or disable overlay
    int enable_overlay = Data[1] % 2;
    if (aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(&codec_ctx, AV1E_SET_ENABLE_OVERLAY, enable_overlay) != AOM_CODEC_OK) {
        return 0;
    }

    // Set maximum consecutive frame drop
    int max_frame_drop = Data[2] % 10;
    if (aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(&codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_frame_drop) != AOM_CODEC_OK) {
        return 0;
    }

    // Set loop filter control
    int loop_filter_control = Data[3] % 2;
    if (aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL(&codec_ctx, AV1E_SET_LOOPFILTER_CONTROL, loop_filter_control) != AOM_CODEC_OK) {
        return 0;
    }

    // Enable or disable directional intra
    int enable_directional_intra = Data[4] % 2;
    if (aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(&codec_ctx, AV1E_SET_ENABLE_DIRECTIONAL_INTRA, enable_directional_intra) != AOM_CODEC_OK) {
        return 0;
    }

    // Set quantizer for one-pass
    int quantizer_one_pass = Data[5] % 63;
    if (aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS(&codec_ctx, AV1E_SET_QUANTIZER_ONE_PASS, quantizer_one_pass) != AOM_CODEC_OK) {
        return 0;
    }

    // Clean up
    aom_codec_destroy(&codec_ctx);
    return 0;
}