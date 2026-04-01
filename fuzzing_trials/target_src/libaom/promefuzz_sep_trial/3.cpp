// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA at aomcx.h:2164:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES at aomcx.h:1998:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE at aomcx.h:1980:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY at aomcx.h:2170:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA at aomcx.h:2290:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX at aomcx.h:2025:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Choose a random control function to call
    int choice = Data[0] % 6;
    Data++;
    Size--;

    // Prepare a dummy value for control functions
    int value = 0;
    if (Size >= sizeof(int)) {
        memcpy(&value, Data, sizeof(int));
    }

    // Initialize the codec interface for AV1
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) return 0;

    // Initialize the codec context
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // A dummy parameter for control functions
    int dummy_param = 0;

    // Invoke the chosen control function
    switch (choice) {
        case 0:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_CFL_INTRA(&codec_ctx, value, dummy_param);
            break;
        case 1:
            aom_codec_control_typechecked_AV1E_SET_COLOR_PRIMARIES(&codec_ctx, value, dummy_param);
            break;
        case 2:
            aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE(&codec_ctx, value, dummy_param);
            break;
        case 3:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY(&codec_ctx, value, dummy_param);
            break;
        case 4:
            aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(&codec_ctx, value, dummy_param);
            break;
        case 5:
            aom_codec_control_typechecked_AV1E_SET_TARGET_SEQ_LEVEL_IDX(&codec_ctx, value, dummy_param);
            break;
        default:
            break;
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}