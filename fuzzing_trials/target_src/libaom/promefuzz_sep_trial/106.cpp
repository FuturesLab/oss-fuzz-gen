// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_EXTERNAL_PARTITION at aomcx.h:2299:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC at aomcx.h:2326:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE at aomcx.h:2019:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE at aomcx.h:1980:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
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

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 6) return 0;

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_codec_err_t res;

    // Initialize encoder configuration
    if ((res = aom_codec_enc_config_default(iface, &cfg, 0)) != AOM_CODEC_OK) {
        return 0;
    }

    // Initialize codec context
    if ((res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0)) != AOM_CODEC_OK) {
        return 0;
    }

    // Use the input data to decide the control values
    int control_value_palette = Data[0];
    int control_value_partition = Data[1];
    int control_value_rtc_rc = Data[2];
    int control_value_color_range = Data[3];
    int control_value_s_frame = Data[4];
    int control_value_color_primaries = Data[5];

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(&codec_ctx, 0, control_value_palette);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_EXTERNAL_PARTITION
    aom_ext_part_funcs_t ext_part_funcs;
    ext_part_funcs.decision_mode = static_cast<aom_ext_part_decision_mode_t>(control_value_partition % 2);
    ext_part_funcs.priv = nullptr;
    res = aom_codec_control_typechecked_AV1E_SET_EXTERNAL_PARTITION(&codec_ctx, 0, &ext_part_funcs);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC
    res = aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC(&codec_ctx, 0, control_value_rtc_rc);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE
    res = aom_codec_control_typechecked_AV1E_SET_COLOR_RANGE(&codec_ctx, 0, control_value_color_range);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE
    res = aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(&codec_ctx, 0, control_value_s_frame);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES
    res = aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, 0, control_value_color_primaries);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Clean up
    aom_codec_destroy(&codec_ctx);
    return 0;
}