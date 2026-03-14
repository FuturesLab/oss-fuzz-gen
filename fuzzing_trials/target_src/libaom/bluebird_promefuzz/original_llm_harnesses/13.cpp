// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA at aomcx.h:2290:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC at aomcx.h:2326:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR at aomcx.h:2365:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR at aomcx.h:2377:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS at aomcx.h:2338:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS at aomcx.h:2347:1 in aomcx.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 5) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) {
        return 0;
    }

    codec_ctx.iface = iface;

    // Prepare a dummy file if needed by any of the functions
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA
    bool enable_diagonal_intra = Data[0] % 2;
    aom_codec_err_t res1 = aom_codec_control_typechecked_AV1E_SET_ENABLE_DIAGONAL_INTRA(
        &codec_ctx, AV1E_SET_ENABLE_DIAGONAL_INTRA, enable_diagonal_intra);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC
    int rtc_external_rc = Data[1];
    aom_codec_err_t res2 = aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC(
        &codec_ctx, AV1E_SET_RTC_EXTERNAL_RC, rtc_external_rc);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR
    int max_consec_frame_drop_cbr = Data[2];
    aom_codec_err_t res3 = aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR(
        &codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, max_consec_frame_drop_cbr);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR
    int max_consec_frame_drop_ms_cbr = Data[3];
    aom_codec_err_t res4 = aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR(
        &codec_ctx, AV1E_SET_MAX_CONSEC_FRAME_DROP_MS_CBR, max_consec_frame_drop_ms_cbr);

    // Fuzz aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS
    int num_operating_points;
    aom_codec_err_t res5 = aom_codec_control_typechecked_AV1E_GET_NUM_OPERATING_POINTS(
        &codec_ctx, AV1E_GET_NUM_OPERATING_POINTS, &num_operating_points);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS
    int quantizer_one_pass = Data[4];
    aom_codec_err_t res6 = aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS(
        &codec_ctx, AV1E_SET_QUANTIZER_ONE_PASS, quantizer_one_pass);

    // Handle cleanup
    if (res1 != AOM_CODEC_OK || res2 != AOM_CODEC_OK || res3 != AOM_CODEC_OK ||
        res4 != AOM_CODEC_OK || res5 != AOM_CODEC_OK || res6 != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    aom_codec_destroy(&codec_ctx);
    return 0;
}