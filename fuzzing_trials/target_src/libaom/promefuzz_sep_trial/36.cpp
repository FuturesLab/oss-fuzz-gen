// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL at aomcx.h:2013:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ at aomcx.h:2350:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING at aomcx.h:1971:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP at aomcx.h:2344:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL at aomcx.h:1968:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
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
#include <exception>
#include <iostream>
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aomdx.h"
#include "aom_external_partition.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));
    codec_ctx.name = "AV1 codec";
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.config.enc = nullptr;
    codec_ctx.priv = nullptr;

    int param1 = 0;
    int param2 = 0;
    memcpy(&param1, Data, sizeof(int));
    memcpy(&param2, Data + sizeof(int), sizeof(int));

    try {
        aom_codec_err_t res;

        // Fuzzing aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL
        res = aom_codec_control_typechecked_AV1E_SET_MAX_GF_INTERVAL(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_SET_MAX_GF_INTERVAL failed with error code " << res << std::endl;
        }

        // Fuzzing aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ
        res = aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_ENABLE_RATE_GUIDE_DELTAQ failed with error code " << res << std::endl;
        }

        // Fuzzing aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING
        res = aom_codec_control_typechecked_AV1E_SET_ENABLE_KEYFRAME_FILTERING(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_SET_ENABLE_KEYFRAME_FILTERING failed with error code " << res << std::endl;
        }

        // Fuzzing aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP
        res = aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_ENABLE_SB_QP_SWEEP failed with error code " << res << std::endl;
        }

        // Fuzzing aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL
        res = aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_SET_ENABLE_TPL_MODEL failed with error code " << res << std::endl;
        }

        // Fuzzing aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC
        res = aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, 0, param1);
        if (res != AOM_CODEC_OK) {
            std::cerr << "Error: AV1E_SET_ENABLE_OBMC failed with error code " << res << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}