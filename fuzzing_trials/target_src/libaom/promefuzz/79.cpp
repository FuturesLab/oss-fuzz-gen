// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS at aomcx.h:2387:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ at aomcx.h:2293:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR at aomcx.h:2359:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING at aomcx.h:1974:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_AQ_MODE at aomcx.h:1983:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING at aomcx.h:2341:1 in aomcx.h
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
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    
    // Initialize codec context
    aom_codec_err_t init_result = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (init_result != AOM_CODEC_OK) return 0;

    // Fuzzing different API functions
    if (Size > 0) {
        // Fuzz adaptive sharpness
        aom_codec_control_typechecked_AV1E_SET_ENABLE_ADAPTIVE_SHARPNESS(&codec_ctx, 0, Data[0] % 2);

        // Fuzz DV cost update frequency
        aom_codec_control_typechecked_AV1E_SET_DV_COST_UPD_FREQ(&codec_ctx, 0, Data[1] % 100);

        // Fuzz bitrate for one-pass CBR
        aom_codec_control_typechecked_AV1E_SET_BITRATE_ONE_PASS_CBR(&codec_ctx, 0, *(reinterpret_cast<const int32_t*>(Data)) % 1000000);

        // Fuzz frame parallel decoding
        aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(&codec_ctx, 0, Data[2] % 2);

        // Fuzz adaptive quantization mode
        aom_codec_control_typechecked_AV1E_SET_AQ_MODE(&codec_ctx, 0, Data[3] % 5);

        // Fuzz skip post-processing filtering
        aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING(&codec_ctx, 0, Data[4] % 2);
    }

    // Cleanup codec context
    aom_codec_destroy(&codec_ctx);
    
    return 0;
}