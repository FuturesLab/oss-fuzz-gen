// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR at aomcx.h:2377:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_TUNING at aomcx.h:1934:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF at aomcx.h:2323:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG at aomcx.h:2264:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS at aomcx.h:2001:1 in aomcx.h
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
#include <cstring>
#include <cstdio>
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < 5) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec context
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, 0)) {
        return 0;
    }

    // Prepare dummy variables for function calls
    int color_primaries = Data[0] % 12;  // Assuming 12 possible color primaries
    int max_consec_frame_drop_ms = Data[1] % 1000; // Arbitrary max drop time
    int tuning = Data[2] % 3;  // Assuming 3 tuning options
    int auto_intra_tools_off = Data[3] % 2; // Boolean for on/off
    int transfer_characteristics = Data[4] % 18; // Assuming 18 possible values

    aom_svc_ref_frame_config_t ref_frame_config;
    memset(&ref_frame_config, 0, sizeof(ref_frame_config));

    // Call the target functions with prepared inputs
    aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, AV1E_SET_COLOR_PRIMARIES, color_primaries);
    aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR(&codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR, max_consec_frame_drop_ms);
    aom_codec_control_typechecked_AOME_SET_TUNING(&codec_ctx, AOME_SET_TUNING, tuning);
    aom_codec_control_typechecked_AV1E_SET_AUTO_INTRA_TOOLS_OFF(&codec_ctx, AV1E_SET_AUTO_INTRA_TOOLS_OFF, auto_intra_tools_off);
    aom_codec_control_typechecked_AV1E_SET_SVC_REF_FRAME_CONFIG(&codec_ctx, AV1E_SET_SVC_REF_FRAME_CONFIG, &ref_frame_config);
    aom_codec_control_typechecked_AV1E_SET_TRANSFER_CHARACTERISTICS(&codec_ctx, AV1E_SET_TRANSFER_CHARACTERISTICS, transfer_characteristics);

    // Clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}