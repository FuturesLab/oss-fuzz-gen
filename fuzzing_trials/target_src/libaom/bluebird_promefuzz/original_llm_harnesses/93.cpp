// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_set_cx_data_buf at aom_encoder.c:244:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

static void fuzz_aom_codec_set_cx_data_buf(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_fixed_buf_t) + 2 * sizeof(unsigned int)) return;

    aom_fixed_buf_t buf;
    buf.buf = const_cast<uint8_t*>(Data);
    buf.sz = Size / 2;

    unsigned int pad_before = Data[Size / 2];
    unsigned int pad_after = Data[Size / 2 + 1];

    aom_codec_err_t res = aom_codec_set_cx_data_buf(ctx, &buf, pad_before, pad_after);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int max_frame_drop = *reinterpret_cast<const int*>(Data);
    aom_codec_err_t res = aom_codec_control(ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_frame_drop);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_rc_funcs_t)) return;

    aom_rc_funcs_t rc_funcs;
    std::memcpy(&rc_funcs, Data, sizeof(aom_rc_funcs_t));

    aom_codec_err_t res = aom_codec_control(ctx, AV1E_SET_EXTERNAL_RATE_CONTROL, &rc_funcs);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int enable_tpl_model = *reinterpret_cast<const int*>(Data);
    aom_codec_err_t res = aom_codec_control(ctx, AV1E_SET_ENABLE_TPL_MODEL, enable_tpl_model);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int enable_rate_guide_deltaq = *reinterpret_cast<const int*>(Data);
    aom_codec_err_t res = aom_codec_control(ctx, AV1E_ENABLE_RATE_GUIDE_DELTAQ, enable_rate_guide_deltaq);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

static void fuzz_aom_codec_control_typechecked_AV1E_SET_AQ_MODE(aom_codec_ctx_t *ctx, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int aq_mode = *reinterpret_cast<const int*>(Data);
    aom_codec_err_t res = aom_codec_control(ctx, AV1E_SET_AQ_MODE, aq_mode);
    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << res << std::endl;
    }
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    std::memset(&codec_ctx, 0, sizeof(codec_ctx));

    fuzz_aom_codec_set_cx_data_buf(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_EXTERNAL_RATE_CONTROL(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_ENABLE_TPL_MODEL(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_ENABLE_RATE_GUIDE_DELTAQ(&codec_ctx, Data, Size);
    fuzz_aom_codec_control_typechecked_AV1E_SET_AQ_MODE(&codec_ctx, Data, Size);

    return 0;
}