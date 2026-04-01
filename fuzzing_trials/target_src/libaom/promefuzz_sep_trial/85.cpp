// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_set_cx_data_buf at aom_encoder.c:244:17 in aom_encoder.h
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
#include <cstring>
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

static void fuzz_aom_codec_set_cx_data_buf(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_fixed_buf_t) + 2 * sizeof(unsigned int)) return;

    aom_fixed_buf_t buf;
    buf.buf = const_cast<uint8_t *>(Data);
    buf.sz = Size;

    unsigned int pad_before = static_cast<unsigned int>(Data[Size - 2]);
    unsigned int pad_after = static_cast<unsigned int>(Data[Size - 1]);

    aom_codec_err_t res = aom_codec_set_cx_data_buf(codec_ctx, &buf, pad_before, pad_after);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_set_cx_data_buf failed with error code: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int force_video_mode = static_cast<int>(Data[0]);
    aom_codec_err_t res = aom_codec_control(codec_ctx, AV1E_SET_FORCE_VIDEO_MODE, force_video_mode);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE failed with error code: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int min_gf_interval = static_cast<int>(Data[0]);
    aom_codec_err_t res = aom_codec_control(codec_ctx, AV1E_SET_MIN_GF_INTERVAL, min_gf_interval);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL failed with error code: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_rc_funcs_t)) return;

    aom_rc_funcs_t rc_funcs;
    memcpy(&rc_funcs, Data, sizeof(aom_rc_funcs_t));

    aom_codec_err_t res = aom_codec_control(codec_ctx, AV1E_SET_EXTERNAL_RATE_CONTROL, &rc_funcs);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL failed with error code: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int max_consec_frame_drop = static_cast<int>(Data[0]);
    aom_codec_err_t res = aom_codec_control(codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_consec_frame_drop);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR failed with error code: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_AQ_MODE(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int aq_mode = static_cast<int>(Data[0]);
    aom_codec_err_t res = aom_codec_control(codec_ctx, AV1E_SET_AQ_MODE, aq_mode);
    if (res != AOM_CODEC_OK) {
        std::cerr << "aom_codec_control_typechecked_AV1E_SET_AQ_MODE failed with error code: " << res << std::endl;
    }
}

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    fuzz_aom_codec_set_cx_data_buf(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MIN_GF_INTERVAL(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_AQ_MODE(&codec_ctx, Data, Size);

    return 0;
}