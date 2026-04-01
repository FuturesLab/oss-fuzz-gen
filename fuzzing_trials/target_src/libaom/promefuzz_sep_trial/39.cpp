// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ at aomcx.h:2350:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SHARPNESS at aomcx.h:1916:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP at aomcx.h:2344:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT at aomcx.h:2049:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION at aomcx.h:2040:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AUTO_TILES at aomcx.h:2368:1 in aomcx.h
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
#include <cstdlib>
#include <iostream>
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

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) {
        return 0; // Not enough data to read two integers
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Failed to initialize codec
    }

    int value1 = *reinterpret_cast<const int*>(Data);
    int value2 = *reinterpret_cast<const int*>(Data + sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ
    res = aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ(&codec_ctx, 0, value1);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_ENABLE_RATE_GUIDE_DELTAQ: " << aom_codec_err_to_string(res) << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AOME_SET_SHARPNESS
    res = aom_codec_control_typechecked_AOME_SET_SHARPNESS(&codec_ctx, 0, value1);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AOME_SET_SHARPNESS: " << aom_codec_err_to_string(res) << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP
    res = aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP(&codec_ctx, 0, value1);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_ENABLE_SB_QP_SWEEP: " << aom_codec_err_to_string(res) << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT
    res = aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT(&codec_ctx, 0, value1);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_DISABLE_TRELLIS_QUANT: " << aom_codec_err_to_string(res) << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION
    res = aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION(&codec_ctx, 0, value1);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_ENABLE_RESTORATION: " << aom_codec_err_to_string(res) << std::endl;
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_AUTO_TILES
    res = aom_codec_control_typechecked_AV1E_SET_AUTO_TILES(&codec_ctx, 0, value2);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error in AV1E_SET_AUTO_TILES: " << aom_codec_err_to_string(res) << std::endl;
    }

    aom_codec_destroy(&codec_ctx);
    return 0;
}