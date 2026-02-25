// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Ensure we have enough data

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 encoder interface
    aom_codec_err_t res;

    // Initialize codec context
    res = aom_codec_enc_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Prepare to test different API functions
    int width = Data[0] % 1920 + 1; // Width between 1 and 1920
    int height = Data[1] % 1080 + 1; // Height between 1 and 1080
    int enable_palette = Data[2] % 2; // 0 or 1
    int quantizer = Data[3] % 64; // Quantizer between 0 and 63
    aom_svc_ref_frame_comp_pred_t svc_pred = { { Data[4] % 2, Data[5] % 2, Data[6] % 2 } };

    // Test setting render size
    aom_codec_control(&codec, AV1E_SET_RENDER_SIZE, width, height);
    
    // Test enabling/disabling palette
    aom_codec_control(&codec, AV1E_SET_ENABLE_PALETTE, enable_palette);
    
    // Test setting quantizer
    aom_codec_control(&codec, AV1E_SET_QUANTIZER_ONE_PASS, quantizer);
    
    // Test setting SVC reference frame compound prediction
    aom_codec_control(&codec, AV1E_SET_SVC_REF_FRAME_COMP_PRED, &svc_pred);

    // Cleanup
    aom_codec_destroy(&codec);
    return 0;
}